

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cr_section_macros.h>

#define EINT0 (1<<0)
#define GPIO22 (1<22)
// TODO: insert other include files here
void configPin(void);
void configInt(void);
// TODO: insert other definitions and declarations here
volatile uint8_t Pulsos = 0; // variable global


int main(void) {
	SystemInit();
	configPin();
	configInt();



    return 0 ;
}

void Systick_Handler(void){
	static uint8_t i = 0;
	if(i<=Pulsos){
		LPC_GPIO0->FIOSET |= (GPIO22); // Cargo Escalo Positivo
	}
	else{
		LPC_GPIO0->FIOCLR |= (GPIO22); // Salida en ) el resto de los ms
	}
	i++;
	if(i==10){
		i=0; // si llega a 10ms reset
	}
	SysTick->CTRL &= SysTick->CTRL;//Limpio Flag Systick al leer registro
}


void EINT0_IRQHandler(void){
	Pulsos ++;
	if(Pulsos==10){ //Cuenta cuantas veces interumpio externamente
		Pulsos=0;
	}
	LPC_SC->EXTINT |= EINT0;//Limpio flag EINT0
}

void configPin(void){
	LPC_PINCON->PINSEL1 &= (~3<<12);//CONFIG GPIO P0.22
	LPC_PINCON->PINSEL4	&= (~1<<20);//CONFIG EINT0 P2.10
	LPC_PINCON->PINSEL4	|= (1<<21);
	LPC_GPIO0->FIODIR2 |= (1<<7); // P0.22 Salida
	LPC_GPIO2->FIODIR1 &= (~1<<2);// P2.10 Entrada
}

void configInt(void){
	LPC_SC->EXTMODE |= EINT0;//sensibilidad por flanco
	LPC_SC->EXTPOLAR &= ~(EINT0);// flanco bajada

	SysTick_Config((SystemCoreClock/1000)); //config Systick

	NVIC_SetPriority(SysTick_IRQn,1); // Asigno prioridad
	NVIC_SetPriority(EINT0_IRQn,2);

	SysTick->CTRL &= SysTick->CTRL;//Limpio Flag Systick al leer registro
	LPC_SC->EXTINT |= EINT0;//Limpio flag EINT0


	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);
}
