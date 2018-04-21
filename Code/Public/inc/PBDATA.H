#ifndef _PBDATA_H__
#define _PBDATA_H__

#include <MATH.H>
#include <STDIO.H>
#include <STRING.H>
#include <INTRINS.H>
#include <STC15F2K60S2.H>

/* *******************************************************************************************
/* 1.根据芯片选择include的芯片头文件(向下兼容，一边情况下不必修改);
/* 2.选择FOSC，并适当修改PARAMETER_US&MS，根据需求选择是否屏蔽.C中的微秒级延时函数;
/* 3.从STC-ISP中导出1US延时函数并在.C中替换;
/* 4.根据是否初一开发者模式选择是否宏定义DeveloperMode；
/* 5.根据工作状态提示灯的位置定义LED及LED的ON/OFF(未设计择不必理会);
/* 6.根据需求选择是否屏蔽数码管字形，位选数组;
/* N.OVER；
/* ******************************************************************************************* */
#define DeveloperMode
//#define USE_SEG

#define PARAMETER_US    13//6       //软件延时时长；
#define PARAMETER_MS    1400//680   //软件延时时长；

#define SysLED          P12         //工作状态提示灯；
#define SysLED_ON       0
#define SysLED_OFF      1
#define SysLED_On();    SysLED=SysLED_ON;
#define SysLED_Off();   SysLED=SysLED_OFF;

#define FOSC            FOSC_24     //系统频率；
#define FOSC_33_1176    (33117600L)
#define FOSC_22_1184    (22118400L)
#define FOSC_18_432     (18432000L)		
#define FOSC_11_0592    (11059200L)		
#define FOSC_5_5296     (5529600L)
#define FOSC_33         (33000000L)
#define FOSC_30         (30000000L)
#define FOSC_27         (27000000L)
#define FOSC_24         (24000000L)
#define FOSC_20         (20000000L)
#define FOSC_12         (12000000L)
#define FOSC_6          (6000000L)

#define TRUE    1
#define FALSE   0
#define u8      unsigned char
#define u16     unsigned int
#define u32     unsigned long
#define uchar   unsigned char       //兼容；
#define uint    unsigned int        //兼容；
#define nop();  _nop_();

#ifdef USE_SEG
#define SEG_NEGATIVE_SIGN   0xBF    //负号显示；
#define SEG_POINT           0x7F    //小数点显示；

extern const u8 code W_Scan[8];
extern const u8 code Seg_7[11];     //数码管字形数组；
#endif

extern void Delay1US();
extern void DelayUS(u16 x);
extern void DelayMS(u16 x);
extern void SysLED_Flash(u16 time, u8 times);

#endif

/* *******************************************************************************************
/* data  固定指片内RAM：    0x00~0x7F
/* bdata 固定指片内RAM：    0x20~0x2F
/* idata 固定指片内RAM：    0x00~0xFF
/* xdata 一般指扩展RAM：    0x0000~0xFFFF，也指STC内部扩展RAM：0x0000~0xFFFF
/* code  指程序存储区ROM：  0x0000~0xFFFF
/* ******************************************************************************************* */

/* *******************************************************************************************
_crol_ 字符循环左移 　　
_cror_ 字符循环右移 　　
_irol_ 整数循环左移 　　
_iror_ 整数循环右移 　　
_lrol_ 长整数循环左移 　　
_lror_ 长整数循环右移 　　
_nop_ 空操作8051 NOP 指令
_testbit_ 测试并清零位8051 JBC 指令 

（_crol_，_irol_，_lrol_）以位形式将val 循环左移n 位，该函数与8051“RLA”指令相关，上面几个函数不同于参数类型。
（_cror_，_iror_，_lror_）以位形式将val 循环右移n 位，该函数与8051“RRA”指令相关，上面几个函数不同于参数类型。 
（_nop_）    产生一个NOP 指令,该函数可用作C 程序的时间比较。C51 编译器在_nop_函数工作期间不产生函数调用，即在程序中直接执行了NOP 指令。
（_testbit_）产生一个JBC 指令，该函数测试一个位，当置位时返回1，否则返回0。如果该位置为1，则将该位复位为0。
             8051 的JBC 指令即用作此目的。_testbit_只能用于可直接寻址的位；在表达式中使用是不允许的。
/* ******************************************************************************************* */

/* *******************************************************************************************
Name        : SPIReadByte(void)
Description : 读SPI数据
Input       : None
Output      : None
Return      : None
/* ******************************************************************************************* */

