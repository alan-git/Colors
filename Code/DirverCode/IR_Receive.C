/* *******************************************************************************************
// Author: biu~
// Last Date:2017/04/07
// 结合LQB写的驱动修改；
/* ******************************************************************************************* */

#include "IR_Receive.H"

sbit IR_Receive = P1^0;
/* *******************************************************************************************
// 函数名称：ReceiveIRdata4()
// 函数功能：红外解码处理
// 在定时器中断中被调用; 
/* ******************************************************************************************* */
bit ReceiveSucceed;     //接收成功标志;
u8 	NECRec[4];          //接收到的所有数据；

void ReceiveIRdata4()
{
    static bit IRsync;                  //是否与发射数据位置同步；
    static u8 bitN;                     //位码装载数；
    static bit IRa,IRb;                 //接收IO状态记录；
    static u16 cntStep;                 //计时基准；

    if (!ReceiveSucceed)
    {
        cntStep++;	
        IRb = IRa;                          //上次电位状态
        IRa = IR_Receive;                   //当前电位状态
        if (IRb && !IRa)                    //是否下降沿（上次高，当前低）
        {
            if(cntStep > Boot_Limit)        //超过同步时间？
            {	
                IRsync=0;                   //同步位清0
            }
            else if(cntStep > Boot_Lower)
            { 
                IRsync=1; 
                bitN=32;                    //同步位置1，装载位码数
            }										  
            else if(IRsync)                 //如果已同步
            {
                if(cntStep > Bit1_Limit)
                {
                    IRsync=0;	           
                }
                else
                {					
                    NECRec[3] >>= 1;	
                    if(cntStep > Bit0_Limit)
                        NECRec[3] |= 0x80;      //“0”与“1”
                    if(--bitN == 0)				
                    {
                        IRsync = 0;             //同步位清0
                        ReceiveSucceed = 1;     //解码有效，不进行数据校验；
                    }
                    else if((bitN & 0x07)== 0)  //NEC[3]每装满8位，移动保存一次（即 BitN%8 == 0）
                    {	
                        NECRec[0]=NECRec[1]; 
                        NECRec[1]=NECRec[2]; 
                        NECRec[2]=NECRec[3];   
                    }
                }
            }
            cntStep = 0;                        //步数计清0
        }
    }
}
