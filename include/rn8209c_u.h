/*************************************************************************
*   	Copyright 2019-2021  MOKO TECHNOLOGY LTD
*
*	Licensed under the Apache License, Version 2.0 (the "License");
*	you may not use this file except in compliance with the License.
*	You may obtain a copy of the License at
*
*	http://www.apache.org/licenses/LICENSE-2.0
*
*	Unless required by applicable law or agreed to in writing, software
*	distributed under the License is distributed on an "AS IS" BASIS,
*	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*	See the License for the specific language governing permissions and
*	limitations under the License.
**************************************************************************/
#ifndef RN8209_U_H__
#define RN8209_U_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "string.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "math.h"
#define DEBUG_8209C

#ifdef DEBUG_8209C
#define rn8209c_debug(...)  printf(__VA_ARGS__)
#else
#define rn8209c_debug(...)
#endif


#define		REG_SYSCON 		0x00
#define        	REG_EMUCON 		0x01
#define        	REG_HFConst     	0x02
#define        	REG_PStart      		0x03
#define        	REG_DStart      		0x04
#define		REG_GPQA        	0x05  //Power correction A
#define        	REG_GPQB        	0x06  //Power correction B
#define        	REG_PhsA        		0x07
#define        	REG_PhsB        		0x08
#define		REG_QPHSCAL		0x09
#define		REG_APOSA 		0x0a
#define        	REG_APOSB 		0x0b
#define        	REG_RPOSA 		0x0c
#define        	REG_RPOSB 		0x0d
#define        	REG_IARMSOS     	0x0e
#define        	REG_IBRMSOS     	0x0f
#define        	REG_IBGain      	0x10
#define		REG_D2FPL       	0x11
#define        	REG_D2FPH       	0x12
#define        	REG_DCIAH       	0x13
#define        	REG_DCIBH       	0x14
#define         REG_DCUH			0x15
#define         REG_DCL   			0x16
#define         REG_EMUCON2		0x17
#define		REG_PFCnt    		0x20
#define        	REG_DFcnt    		0x21
#define        	REG_IARMS       	0x22  //current a
#define        	REG_IBRMS       	0x23  //current b
#define        	REG_URMS        	0x24   //vlotage
#define		REG_UFreq       	0x25
#define        	REG_PowerPA     	0x26
#define        	REG_PowerPB     	0x27
#define        	REG_PowerQ     	0x28
#define         REG_EnergyP  		0x29
#define         REG_EnergyP2 		0x2a
#define         REG_EnergyD  		0x2b
#define         REG_EnergyD2    	0x2c
#define         REG_EMUStatus   	0x2d	//???��??��??��
#define         REG_SPL_IA      	0x30
#define         REG_SPL_IB      	0x31
#define         REG_SPL_U       	0x32
#define         REG_IE  			0x40
#define         REG_IF  			0x41
#define         REG_RIF    			0x42
#define         REG_SysStatus  	0x43
#define         REG_RData      		0x44
#define         REG_WData      		0x45
#define         REG_DeviceID   	0x7f
#define         REG_WriteEn   		0xea

//#define HFCONST  0x42e6

//#define KP        0.0000136867


#define VOLTAGE_REF  220
#define CURRENT_REF  5


#define CMD_WAIT_MS   40
#define RN8209_CMD_REPEAT_TIMES  3

#define phase_A   0
#define phase_B (1+phase_A)


typedef void (*rn8209c_delay_ms_fun)(int ms);
typedef void (*rn8209c_uart_tx_fun)(uint8_t *dataout,int len);
typedef int (*rn8209c_uart_rx_fun)(uint8_t *dataout,int len,int time_out);
typedef void (*rn8209c_tx_pin_reset_fun)(void);

typedef struct
{
    float power_start;  //��������
    uint32_t EC;  //���峣��
    float KV;  //��ѹϵ��
    uint32_t  R;  //��������
    uint16_t GPQA;    //Aͨ����������У��-----------------
    uint16_t GPQB;    //Bͨ����������У��
    uint8_t  PhsA;    //Aͨ����λУ��--------------------------
    uint8_t  PhsB;    //Bͨ����λУ��
    uint16_t Cst_QPhsCal; //�޹���λУ��------------------------
    uint16_t APOSA;   //Aͨ���й�����offsetУ��--------------------
    uint16_t APOSB;   //Bͨ���й�����offsetУ��
    uint16_t RPOSA;   //Aͨ���޹�����offsetУ��
    uint16_t RPOSB;   //Bͨ���޹�����offsetУ��
    uint16_t IARMSOS; //Aͨ��������ЧֵoffsetУ��------------------
    uint16_t IBRMSOS; //Bͨ��������ЧֵoffsetУ��
    uint16_t IBGain;  //Bͨ����������

    uint32_t Ku;//��ѹ����-----------------
    uint32_t Kia;//--------------------
    uint32_t Kib;
    uint16_t deviation;//���
}__attribute__((packed)) STU_8209C;



//extern STU_8209C Stu8209c;
bool rn8209c_init( rn8209c_delay_ms_fun delay,\
                  rn8209c_uart_tx_fun uart_tx,\
                  rn8209c_uart_rx_fun uart_rx,\
                  rn8209c_tx_pin_reset_fun tx_pin_reset,\
                  STU_8209C param);/*�ӿڳ�ʼ��*/


uint8_t rn8209c_init_para( void);

uint8_t rn8209c_read_voltage(uint32_t *vol);/*����1000��*/
uint8_t rn8209c_read_current(uint8_t phase,uint32_t *current);/* ����10000��*/
uint8_t rn8209c_read_power(uint8_t phase,uint32_t *p);/*����10000��*/
uint8_t rn8209c_read_power_energy(uint8_t phase,uint32_t *p); /*����1000��*/
uint8_t rn8209c_read_power_Q(uint8_t phase,uint32_t *p);/*����10000*/
uint8_t rn8209c_read_emu_status(void);

void rn8209c_calibrate_voltage_current(uint8_t phase,uint32_t voltage_real,uint32_t current_real );  /*1.0 ��У��̨��ѹ����220V,5A, 1.0����У׼*/
void rn8209c_calibrate_power_k(uint8_t phase,uint32_t ku,uint32_t ki);/*2.0 ��У��̨��ѹ����220V,5A, 1.0����У׼*/
void rn8209c_calibrate_phs(uint8_t phase,uint32_t power_ref);/* 3 .0 ��У��̨��ѹ����220V,5A��0.5L*/
void rn8209c_calibrate_power_offset(uint8_t phase,uint32_t power_ref);/* 4.0 5% Ib ����OffsetУ�� ��У��̨��ѹ����220V,0.25A,1.0 */
void rn8209c_calibrate_power_Q(uint8_t phase,uint32_t power_q_ref);/*5.0 ��У��̨��ѹ����220V,16A, 0.5�޹�У׼*/
void rn8209c_calibrate_current_offset(uint8_t phase) ;/*6.0 ����OffsetУ����У��̨��ѹ����220V,0A,1.0��ֻ�ṩ��ѹ*/

STU_8209C read_stu8209c_calibrate_param(void);
void rn8209c_calibrate_power_k_phase_a(void);
void rn8209c_calibrate_power_k_phase_b(void);
uint8_t rn8209c_read_energy(uint32_t *energy);
extern  float  kp;

#ifdef __cplusplus
}
#endif

#endif





















