#ifndef __DELAY_H
#define __DELAY_H 			   

//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
//�汾��V1.2
//V1.2�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!
////////////////////////////////////////////////////////////////////////////////// 
void Delay_Init(int8u SYSCLK);
void Delay_ms(int16u nms);
void Delay_us(int32u nus);

#endif
