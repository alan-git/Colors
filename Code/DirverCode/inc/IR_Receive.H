#ifndef _IR_Receive_H__
#define _IR_Receive_H__

#include "INCLUDES.H"

    // 69 70 71  //0xBA 0xB8 0x
    // 68 64 67
    // 69 70 71
    // 69 70 71
    // 69 70 71
/* *******************************************************************************************
/* 1.根据所采用的时钟选择SET_T0/T1/.._TIME；
/* 1.观察定时器中断溢出频率是否合适；
/* N.OVER；
/* ******************************************************************************************* */
#define TIMER_TIME SET_T0_TIME

#define Boot_Limit (((9000+4500)+2000)/(TIMER_TIME))  //引导码周期上限    
#define Boot_Lower (((9000+4500)-2000)/(TIMER_TIME))  //引导码周期下限    
#define Bit1_Limit ((2250+800)/(TIMER_TIME))          //“1”周期上限
#define Bit0_Limit ((1125+400)/(TIMER_TIME))          //“0”周期上限

extern u8 NECRec[4];                //接收到的所有数据；
extern bit ReceiveSucceed;          //接收成功标志;	
extern void ReceiveIRdata4();       //红外解码处理;

#endif