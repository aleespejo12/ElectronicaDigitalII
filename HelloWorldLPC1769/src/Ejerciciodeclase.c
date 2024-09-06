/*
===============================================================================
 Name        : Ejercicio 1
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <cr_section_macros.h>

// Function prototypes
void configSystick(void);
void configPin(void);
int read_pin_value(void);

// Global variables
static uint8_t Salida_1 = 0;
static uint8_t Salida_2 = 0;

int main(void) {
    SystemInit();
    configPin();
    configSystick();
    int statePrevio = 1;

    while (1) {
        int stateButton = read_pin_value();
        if (statePrevio == 1 && stateButton == 0) {
            LPC_GPIO0->FIOPIN ^= (Salida_1 << 19);  
            LPC_GPIO0->FIOPIN ^= (Salida_2 << 15);  
        }
        if (statePrevio == 0 && stateButton == 0) {
            LPC_GPIO0->FIOPIN ^= (Salida_1 << 15);  
            LPC_GPIO0->FIOPIN ^= (Salida_2 << 19);  
            statePrevio = 1;
        }
        statePrevio = stateButton;
    }

    return 0;
}

void Systick_Handler(void) {
    static uint8_t counter_5ms = 0;
    static uint8_t counter_25ms = 0;

    counter_5ms++;
    if (counter_5ms == 5) {
        counter_25ms++;
        counter_5ms = 0;
        Salida_1 ^= 1;  // Toggle Salida_1
    }
    if (counter_25ms >= 7) {
        Salida_1 = 1;
        Salida_2 ^= 1;  // Toggle Salida_2
        if (counter_25ms == 14) {
            counter_25ms = 0;
        }
    }
}

void configPin(void) {
    LPC_PINCON->PINSEL0 &= ~(3 << 15);  // GPIO function for P0.7
    LPC_PINCON->PINSEL1 &= ~(3 << 19) & ~(3 << 23);  // GPIO function for P0.15 and P0.23
    LPC_PINCON->PINMODE1 &= ~(3 << 23);  // Default pull-up for P0.23
    LPC_GPIO0->FIODIR |= (1 << 15);  // Set P0.15 as output
    LPC_GPIO0->FIODIR |= (1 << 19);  // Set P0.19 as output
    LPC_GPIO0->FIODIR &= ~(1 << 23);  // Set P0.23 as input
}

void configSystick(void) {
    if (SysTick_Config(SystemCoreClock / 200)) {
        while (1);  // Error, infinite loop
    }
}

int read_pin_value(void) {
    return (LPC_GPIO0->FIOPIN >> 23) & 0x1;
}
