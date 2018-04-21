#ifndef _TIME_BASE_H__
#define _TIME_BASE_H__

#include "INCLUDES.H"

/* *******************************************************************************************
/* 1.����STC-ISP������������ Timer0Init/Timer1Init/...��
/* 2.#define T_0/T_1/...;
/* 3.�޸Ķ�ʱ��0/1/...���ʱ����
/* 4.ѡȡһ����׼ʱ��(TIME_BASE_1ST/2ND)��
/* N.OVER��
/* ******************************************************************************************* */
#define T_0
//#define T_1
//#define T_2

#ifdef T_0
    #define SET_T0_TIME             (50L)          //��ʱ��0���ʱ����
    #define TIMING_DELAY_USE_TIMER  SET_T0_TIME
#elif T_1
    #define SET_T1_TIME             (2000L)         //��ʱ��1���ʱ����
    #define TIMING_DELAY_USE_TIMER  SET_T1_TIME	
#elif T_2
    #define SET_T2_TIME             (2000L)         //��ʱ��2���ʱ����
    #define TIMING_DELAY_USE_TIMER  SET_T2_TIME	
#endif
//#endif

#define _400US     (400L)                                //�Զ����׼ʱ��(���ʱ����������)��

#define TIME_BASE_1ST       _400US                          //��׼ʱ��1���壻
#define TIME_BASE_2ND       _20MS                           //��׼ʱ��2���壻
#define TIME_BASE_3RD       _5MS                            //��׼ʱ��3���壻

#define OVERFLOW_TIMES_1ST  (TIME_BASE_1ST/TIMING_DELAY_USE_TIMER)//������ѡ��׼ʱ�䣬��ʱ�������������
#define OVERFLOW_TIMES_2ND  (TIME_BASE_2ND/TIMING_DELAY_USE_TIMER)//������ѡ��׼ʱ�䣬��ʱ�������������
#define OVERFLOW_TIMES_3RD  (TIME_BASE_3RD/TIMING_DELAY_USE_TIMER)//������ѡ��׼ʱ�䣬��ʱ�������������
#define _60S        (60000000L)
#define _20S        (20000000L)
#define _10S        (10000000L)
#define _5S         (5000000L)
#define _2S         (2000000L)
#define _1S         (1000000L)
#define _500MS      (500000L)
#define _200MS      (200000L)
#define _100MS      (100000L)
#define _50MS       (50000L)
#define _20MS       (20000L)        //50HZ
#define _10MS       (10000L)
#define _5MS        (5000L)
#define _2MS        (2000L)

extern void InitInterrupt();

#endif			  	 