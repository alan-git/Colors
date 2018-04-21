/* *******************************************************************************************
// Author: biu~
// Last Date:2017/04/07
// ���LQBд�������޸ģ�
/* ******************************************************************************************* */

#include "IR_Receive.H"

sbit IR_Receive = P1^0;
/* *******************************************************************************************
// �������ƣ�ReceiveIRdata4()
// �������ܣ�������봦��
// �ڶ�ʱ���ж��б�����; 
/* ******************************************************************************************* */
bit ReceiveSucceed;     //���ճɹ���־;
u8 	NECRec[4];          //���յ����������ݣ�

void ReceiveIRdata4()
{
    static bit IRsync;                  //�Ƿ��뷢������λ��ͬ����
    static u8 bitN;                     //λ��װ������
    static bit IRa,IRb;                 //����IO״̬��¼��
    static u16 cntStep;                 //��ʱ��׼��

    if (!ReceiveSucceed)
    {
        cntStep++;	
        IRb = IRa;                          //�ϴε�λ״̬
        IRa = IR_Receive;                   //��ǰ��λ״̬
        if (IRb && !IRa)                    //�Ƿ��½��أ��ϴθߣ���ǰ�ͣ�
        {
            if(cntStep > Boot_Limit)        //����ͬ��ʱ�䣿
            {	
                IRsync=0;                   //ͬ��λ��0
            }
            else if(cntStep > Boot_Lower)
            { 
                IRsync=1; 
                bitN=32;                    //ͬ��λ��1��װ��λ����
            }										  
            else if(IRsync)                 //�����ͬ��
            {
                if(cntStep > Bit1_Limit)
                {
                    IRsync=0;	           
                }
                else
                {					
                    NECRec[3] >>= 1;	
                    if(cntStep > Bit0_Limit)
                        NECRec[3] |= 0x80;      //��0���롰1��
                    if(--bitN == 0)				
                    {
                        IRsync = 0;             //ͬ��λ��0
                        ReceiveSucceed = 1;     //������Ч������������У�飻
                    }
                    else if((bitN & 0x07)== 0)  //NEC[3]ÿװ��8λ���ƶ�����һ�Σ��� BitN%8 == 0��
                    {	
                        NECRec[0]=NECRec[1]; 
                        NECRec[1]=NECRec[2]; 
                        NECRec[2]=NECRec[3];   
                    }
                }
            }
            cntStep = 0;                        //��������0
        }
    }
}