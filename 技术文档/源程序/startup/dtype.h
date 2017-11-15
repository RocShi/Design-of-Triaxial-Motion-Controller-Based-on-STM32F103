
/**--------------File Info---------------------------------------------------------------------------------
** File name:			dtype.h
** modified Date:  		2013-1-5
** Last Version:		V2.00
** Descriptions:		���幤��Ҫ�õ����������ͣ������������Ӧ�ô��붼Ӧ��ʹ�ñ��ļ��ﶨ�����������
**	
*********************************************************************************************************/
#ifndef _DTYPE_H_
#define _DTYPE_H_     //����������Ϊ�˱���ͬһ���ļ��ظ�������ͷ�ļ�

/*********************************************************************************************************
  /�������ݵĶ�д���ԣ���������Χ�Ĵ����Ĵ洢����
*********************************************************************************************************/
#define     __I     volatile const    //ֻ�� 
#define     __O     volatile          //ֻд
#define     __IO    volatile          //��д

/*********************************************************************************************************
  �����������Ͷ���
*********************************************************************************************************/
typedef unsigned char  int8u;         //�޷���8λ���ͱ��� 
typedef signed   char  int8s;		  //�з���8λ���ͱ��� 
typedef unsigned short int16u;        //�޷���16λ���ͱ���
typedef signed   short int16s;        //�з���16λ���ͱ���
typedef unsigned int   int32u;        //�޷���32λ���ͱ���
typedef signed   int   int32s;        //�з���32λ���ͱ��� 
typedef float          fp32;          //�����ȸ�������32λ���ȣ�
typedef double         fp64;          //˫���ȸ�������64λ���ȣ�
									  
/*********************************************************************************************************
  STM32F10X ��׼�������õ����������Ͷ���
*********************************************************************************************************/
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;
typedef int32_t   s32;
typedef int16_t   s16;
typedef int8_t    s8;
typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;	
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#endif  //_DTYPE_H_
