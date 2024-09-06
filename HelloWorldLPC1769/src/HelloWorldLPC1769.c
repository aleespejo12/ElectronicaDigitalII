/*
===============================================================================
 Nombre       : Ejercicio 1
 Autor        : $(author)
 Versión      :
 Derechos     : $(copyright)
 Descripción  : definición principal
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <cr_section_macros.h>

// Prototipos de funciones
void configSystick(void);
void configPin(void);
int read_pin_value(void);

// Variables globales
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
            LPC_GPIO0->FIOPIN ^= (Salida_1 << 19);  // Cambiar el estado del pin 19
            LPC_GPIO0->FIOPIN ^= (Salida_2 << 15);  // Cambiar el estado del pin 15
        }
        if (statePrevio == 0 && stateButton == 0) {
            LPC_GPIO0->FIOPIN ^= (Salida_1 << 15);  // Cambiar el estado del pin 15
            LPC_GPIO0->FIOPIN ^= (Salida_2 << 19);  // Cambiar el estado del pin 19
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
        Salida_1 ^= 1;  // Cambiar el estado de Salida_1
    }
    if (counter_25ms >= 7) {
        Salida_1 = 1;
        Salida_2 ^= 1;  // Cambiar el estado de Salida_2
        if (counter_25ms == 14) {
            counter_25ms = 0;
        }
    }
}

void configPin(void) {
    LPC_PINCON->PINSEL0 &= ~(3 << 15);  // Función GPIO para P0.7
    LPC_PINCON->PINSEL1 &= ~(3 << 19) & ~(3 << 23);  // Función GPIO para P0.15 y P0.23
    LPC_PINCON->PINMODE1 &= ~(3 << 23);  // Pull-up por defecto para P0.23
    LPC_GPIO0->FIODIR |= (1 << 15);  // Configurar P0.15 como salida
    LPC_GPIO0->FIODIR |= (1 << 19);  // Configurar P0.19 como salida
    LPC_GPIO0->FIODIR &= ~(1 << 23);  // Configurar P0.23 como entrada
}

void configSystick(void) {
    if (SysTick_Config(SystemCoreClock / 200)) {
        while (1);  // Error, bucle infinito
    }
}

int read_pin_value(void) {
    return (LPC_GPIO0->FIOPIN >> 23) & 0x1;
}
