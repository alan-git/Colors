#ifndef _IR_Receive_H__
#define _IR_Receive_H__

#include "INCLUDES.H"

    // 69 70 71  //0xBA 0xB8 0x
    // 68 64 67
    // 69 70 71
    // 69 70 71
    // 69 70 71
/* *******************************************************************************************
/* 1.���������õ�ʱ��ѡ��SET_T0/T1/.._TIME��
/* 1.�۲춨ʱ���ж����Ƶ���Ƿ���ʣ�
/* N.OVER��
/* ******************************************************************************************* */
#define TIMER_TIME SET_T0_TIME

#define Boot_Limit (((9000+4500)+2000)/(TIMER_TIME))  //��������������    
#define Boot_Lower (((9000+4500)-2000)/(TIMER_TIME))  //��������������    
#define Bit1_Limit ((2250+800)/(TIMER_TIME))          //��1����������
#define Bit0_Limit ((1125+400)/(TIMER_TIME))          //��0����������

extern u8 NECRec[4];                //���յ����������ݣ�
extern bit ReceiveSucceed;          //���ճɹ���־;	
extern void ReceiveIRdata4();       //������봦��;

#endif