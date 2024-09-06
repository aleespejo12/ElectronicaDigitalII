

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cr_section_macros.h>
#define TRUE 1
#define FALSE 0

volatile bool Variador = TRUE;
// TODO: insert other include files here

// TODO: insert other definitions and declarations here
void configPin(void);
void retardo(uint32_t);
void configSystick();

int main(void) {
	SystemInit();
	configPin();
	configSystick();
	uint32_t time=100000;


	while(1){
		retardo(time);
		if(Variador==TRUE){
			Variador=FALSE;
		}
		else{
			Variador=TRUE;
		}

	}
    return 0 ;
}

void retardo(volatile uint32_t time){
	while(time > 0){
		time--;
	}
}


void Systick_Handler(void){
	static uint8_t counterSys = 10;
	static uint8_t counterSecA = 0;

	counterSys--;
	if(Variador==TRUE){
		if(counterSys==0){
			LPC_GPIO0->FIOCLR = (0xFFFFFFFF);
			LPC_GPIO0->FIOSET = (1<<counterSecA);
			counterSecA++;

			if(counterSecA==11){
				counterSecA=0;
			}
			counterSys=10;
		}
	}
	else{
		if(counterSys==0){
					LPC_GPIO0->FIOCLR = (0xFFFFFFFF);
					LPC_GPIO0->FIOSET = (1<<(10-counterSecA));
					counterSecA++;

					if(counterSecA==11){
						counterSecA=0;
					}
					counterSys=10;
				}
	}


}

void configSystick(void){
	if(SysTick_Config(SystemCoreClock/100)){
		while(1);
	}

}

void configPin(void){
	LPC_PINCON->PINSEL0 &= (~0x7FFFF);
	LPC_PINCON->PINMODE0 |= 0x7FFFF;
	LPC_GPIO0->FIODIR |= 0x3FF;

}
