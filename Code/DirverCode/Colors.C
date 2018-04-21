/* *******************************************************************************************
// Author: biu~
// Last Date:2018/04/20
/* ******************************************************************************************* */
#include "Colors.H"

#define PWM_DUTY_MAX    255 // 0~255    PWM周期, 最大255
#define PWM_ON          0   // 定义占空比的电平, 1 或 0
#define PWM_OFF         (!PWM_ON)

#define PWM_BLUE    0
#define PWM_GREEN   1
#define PWM_RED     2

#define PWM_ACCELERATE1 0xA0
#define PWM_ACCELERATE2 0xC7
sbit Color_Blue = P3^1;
sbit Color_Green = P3^2;
sbit Color_Red = P3^3;
data u8 PwmDuty[3];
/* *******************************************************************************************
// 定时器PWM输出初始化：
/* ******************************************************************************************* */
void TimerPWM_Init()
{
    PwmDuty[PWM_BLUE] = 0x00;
    PwmDuty[PWM_GREEN] = 0x00;
    PwmDuty[PWM_RED] = 0x00;
}
          
/* *******************************************************************************************
// 定时器控制PWM输出 
/* ******************************************************************************************* */
void TimerPWM()
{
    static idata u8 temp_pwm_duty = 0;
    if(temp_pwm_duty == PwmDuty[PWM_BLUE]) Color_Blue = PWM_OFF;       //判断PWM占空比是否结束
    if(temp_pwm_duty == PwmDuty[PWM_GREEN]) Color_Green = PWM_OFF;
    if(temp_pwm_duty == PwmDuty[PWM_RED]) Color_Red = PWM_OFF;
        
    if(++temp_pwm_duty == PWM_DUTY_MAX)                 //PWM周期结束，重新开始新的周期
    {
        temp_pwm_duty = 0;
        if (PwmDuty[PWM_BLUE] != 0)                     //在PWM占空为0时不开启灯光；
            Color_Blue = PWM_ON;
        if (PwmDuty[PWM_GREEN] != 0)
            Color_Green = PWM_ON;
        if (PwmDuty[PWM_RED] != 0)
            Color_Red = PWM_ON;
    }
}

/* *******************************************************************************************
// PWM占空改变功能函数：某_bit（颜色）占空比增加至 temp_pwm
/* ******************************************************************************************* */
bit TimerPWM_Duty_Add(u8 _bit, u8 temp_pwm)
{
    if (temp_pwm > PwmDuty[_bit])
    {
        if (PwmDuty[_bit] >= PWM_ACCELERATE2 && PwmDuty[_bit] < 0xFD)   //亮度较高时，由于人眼对较亮的灯光亮度改变感受不明显，进行加速处理；
        {
            PwmDuty[_bit] += 3;
        }
        else if (PwmDuty[_bit] >= PWM_ACCELERATE1 && PwmDuty[_bit] < 0xFE)
        {
            PwmDuty[_bit] += 2;
        }
        else
        {
            PwmDuty[_bit] ++;
        }
    }  
    else 
    {
        return 1;
    }  
    return 0;
}

/* *******************************************************************************************
// PWM占空改变功能函数：某_bit（颜色）占空比减至 temp_pwm
/* ******************************************************************************************* */
bit TimerPWM_Duty_Dec(u8 _bit, u8 temp_pwm)
{
    if (temp_pwm < PwmDuty[_bit])
    {
        if (PwmDuty >= PWM_ACCELERATE2) //亮度较高时，由于人眼对较亮的灯光亮度改变感受不明显，进行加速处理；
        {
            PwmDuty[_bit] -= 3;
        }
        else if (PwmDuty[_bit] >= PWM_ACCELERATE1)
        {
            PwmDuty[_bit] -= 2;
        }
        else
        {
            PwmDuty[_bit] --;
        }
    }
    else 
    {
        return 1;
    }  
    return 0;
}

#define DEC 0
#define ADD 1

#define BLUE_RED    1
#define BLUE_GREEN  2
#define RED_GREEN   3
/* *******************************************************************************************
// 多（双）颜色亮度控制
/* ******************************************************************************************* */
static bit conColorsPWM(u8 colors, bit color1_dec_or_inc, u8 temp_color1, bit color2_dec_or_inc, u8 temp_color2)
{
    auto u8 count = 0;
    switch (colors)
    {
        case BLUE_RED:
        {
            if ((color1_dec_or_inc == DEC) ? TimerPWM_Duty_Dec(PWM_BLUE, temp_color1) : TimerPWM_Duty_Add(PWM_BLUE, temp_color1))
            {
                count ++;
            }
            if ((color2_dec_or_inc == DEC) ? TimerPWM_Duty_Dec(PWM_RED, temp_color2) : TimerPWM_Duty_Add(PWM_RED, temp_color2))
            {
                count ++;
            }
        }
            break;
        case BLUE_GREEN:
        {
            if ((color1_dec_or_inc == DEC) ? TimerPWM_Duty_Dec(PWM_BLUE, temp_color1) : TimerPWM_Duty_Add(PWM_BLUE, temp_color1))
            {
                count ++;
            }
            if ((color2_dec_or_inc == DEC) ? TimerPWM_Duty_Dec(PWM_GREEN, temp_color2) : TimerPWM_Duty_Add(PWM_GREEN, temp_color2))
            {
                count ++;
            }
        }
            break;
        case RED_GREEN:
        {
            if ((color1_dec_or_inc == DEC) ? TimerPWM_Duty_Dec(PWM_RED, temp_color1) : TimerPWM_Duty_Add(PWM_RED, temp_color1))
            {
                count ++;
            }
            if ((color2_dec_or_inc == DEC) ? TimerPWM_Duty_Dec(PWM_GREEN, temp_color2) : TimerPWM_Duty_Add(PWM_GREEN, temp_color2))
            {
                count ++;
            }
        }
            break;
        default:
            break;
    }
    return ((count == 2) ? 1 : 0);
}

/* *******************************************************************************************
// 所有颜色渐熄
/* ******************************************************************************************* */
static bit conAllColorsOff()
{
    auto u8 count = 0;
    if (TimerPWM_Duty_Dec(PWM_BLUE, 0))
    {
        count ++;
    }
    if (TimerPWM_Duty_Dec(PWM_GREEN, 0))
    {
        count ++;
    }
    if (TimerPWM_Duty_Dec(PWM_RED, 0))
    {
        count ++;
    }
    return ((count == 3) ? 1 : 0);
}

#define SLOW 0
#define FAST 1

bit conSpeed = SLOW;
/* *******************************************************************************************
// PWM占空比改变控制：慢速
/* ******************************************************************************************* */
void Con_TimerPWM_Duty_Slow()
{
    static u8 mode = 0;         //当前模式；
    if (conSpeed == SLOW)
    {
        switch (mode)
        {
//            case 0: if(TimerPWM_Duty_Add(PWM_BLUE, 255) == 1) {mode ++;}
            case 0: if(TimerPWM_Duty_Add(PWM_BLUE, 255)) {mode ++;}
                break; 
            case 1: if(TimerPWM_Duty_Dec(PWM_BLUE, 0)) {mode ++;}
                break;
            case 2: if(TimerPWM_Duty_Add(PWM_RED, 255)) {mode ++;}
                break;
            case 3: if(TimerPWM_Duty_Dec(PWM_RED, 80)) {mode ++; conSpeed = FAST;}
                break;
#define BLUE_RED    1
#define BLUE_GREEN  2
#define RED_GREEN   3
#define DEC 0
#define ADD 1
            case 4: if(conColorsPWM(BLUE_RED, ADD, 120, ADD, 200)) {mode ++;} 
                break;
            case 5: if(conColorsPWM(BLUE_RED, ADD, 230, ADD, 255)) {mode ++;}
                break;
            case 6: if (conAllColorsOff()) {mode ++;}
                break;                                                                                                      
            case 7: if(conColorsPWM(BLUE_GREEN, ADD, 50, ADD, 230)) {mode ++;}
                break;
            case 8: if(conColorsPWM(RED_GREEN, ADD, 255, DEC, 0)) {mode ++;}
                break;
            case 9: if(conAllColorsOff()) {mode ++; conSpeed = FAST;}
                break;
            case 10: if(conColorsPWM(BLUE_RED, ADD, 80, ADD, 200)) {mode ++;}
                break;
            case 11: if(conColorsPWM(BLUE_RED, ADD, 230, ADD, 255)) {mode ++;}
                break;
            case 12: if(conAllColorsOff()) {mode ++;}
                break;
            case 13: if(conColorsPWM(RED_GREEN, ADD, 20, ADD, 255)) {mode ++;}
                break;
            case 14: if(conAllColorsOff()) {mode ++;}
                break;
            case 15: if(conColorsPWM(BLUE_GREEN, ADD, 50, ADD, 230)) {mode ++; conSpeed = FAST;}
                break;
            default:if(conAllColorsOff()) {mode = 0;}
                break;
        }
    }
}

/* *******************************************************************************************
// PWM占空比改变控制：快速
/* ******************************************************************************************* */
void Con_TimerPWM_Duty_Fast()
{
    static u8 mode = 0;         //当前模式；
    if (conSpeed == FAST)
    {
        switch (mode)
        {
            case 0: if(TimerPWM_Duty_Add(PWM_GREEN, 255)) {mode ++;}
                break;
            case 1: if(TimerPWM_Duty_Dec(PWM_GREEN, 120)) {mode ++;}
                break;
            case 2: if(TimerPWM_Duty_Add(PWM_BLUE, 60)) {mode ++;}
                break;
            case 3: if(conColorsPWM(BLUE_GREEN, DEC, 0, ADD, 90)) {mode ++;}
                break;
            case 4: if(conColorsPWM(RED_GREEN, ADD, 255, ADD, 240)) {mode ++;}
                break;
            case 5: if(conColorsPWM(RED_GREEN, DEC, 230, DEC, 140)) {mode ++;}
                break;
            case 6: if(conColorsPWM(BLUE_GREEN, ADD, 255, ADD, 230)) {mode ++;}
                break;
            case 7: if(conAllColorsOff()) {mode ++; conSpeed = SLOW;}
                break;
            case 8: if(TimerPWM_Duty_Add(PWM_RED, 255)) {mode ++;}
                break;
            case 9: if(conColorsPWM(BLUE_RED, ADD, 255, DEC, 120)) {mode ++;}
                break;
            case 10: if(TimerPWM_Duty_Dec(PWM_BLUE, 180)) {mode ++;}
                break;
            case 11: if(conColorsPWM(BLUE_GREEN, DEC, 180, ADD, 255)) {mode ++; conSpeed = SLOW;}
                break;
            default:if(conAllColorsOff()) {mode = 0;}
                break;
        }
    }
}
