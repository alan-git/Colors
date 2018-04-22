#ifndef _TIME_BASE_H__
#define _TIME_BASE_H__

#include "INCLUDES.H"

/* *******************************************************************************************
/* 1.利用STC-ISP软件导出函数 Timer0Init/Timer1Init/...；
/* 2.#define T_0/T_1/...;
/* 3.修改定时器0/1/...溢出时长；
/* 4.选取一个基准时间(TIME_BASE_1ST/2ND)；
/* N.OVER；
/* ******************************************************************************************* */
#define T_0
//#define T_1
//#define T_2

#ifdef T_0
    #define SET_T0_TIME             (50L)          //定时器0溢出时长；
    #define TIMING_DELAY_USE_TIMER  SET_T0_TIME
#elif T_1
    #define SET_T1_TIME             (2000L)         //定时器1溢出时长；
    #define TIMING_DELAY_USE_TIMER  SET_T1_TIME	
#elif T_2
    #define SET_T2_TIME             (2000L)         //定时器2溢出时长；
    #define TIMING_DELAY_USE_TIMER  SET_T2_TIME	
#endif
//#endif

#define _400US     (400L)                                //自定义基准时长(溢出时长的整数倍)；

#define TIME_BASE_1ST       _400US                          //基准时间1定义；
#define TIME_BASE_2ND       _20MS                           //基准时间2定义；
#define TIME_BASE_3RD       _5MS                            //基准时间3定义；

#define OVERFLOW_TIMES_1ST  (TIME_BASE_1ST/TIMING_DELAY_USE_TIMER)//计满所选基准时间，定时器的溢出次数；
#define OVERFLOW_TIMES_2ND  (TIME_BASE_2ND/TIMING_DELAY_USE_TIMER)//计满所选基准时间，定时器的溢出次数；
#define OVERFLOW_TIMES_3RD  (TIME_BASE_3RD/TIMING_DELAY_USE_TIMER)//计满所选基准时间，定时器的溢出次数；
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
#define _1MS        (1000L)

extern void InitInterrupt();

#endif			  	 
