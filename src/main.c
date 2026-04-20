//********************************************************************
//*                    MEC4126F C template                           *
//*==================================================================*
//* WRITTEN BY: James Hepworth   	                 	             *
//* DATE CREATED: 2025/04/08                                         *
//*==================================================================*
//* PROGRAMMED IN: Visual Studio Code                                *
//* TARGET:        STM32F051                                         *
//*==================================================================*
//* DESCRIPTION:     Template for MEC4126F C Practicals              *
//********************************************************************

//====================================================================
// INCLUDE FILES
//====================================================================

#define STM32F051
#include "stm32f0xx.h"											   
#include "lcd_stm32f0.h"
#include <stdio.h>
#include <stdint.h>

//====================================================================
// GLOBAL CONSTANTS
//====================================================================

//====================================================================
// GLOBAL VARIABLES
//====================================================================

//====================================================================
// FUNCTION DECLARATIONS
//====================================================================

void init_student(void);
void init_ADC(void);

//====================================================================
// MAIN FUNCTION
//====================================================================

int main (void)
{
    init_student();
    
    while (1)
    {
    }

}							
// End of main

//====================================================================
// FUNCTION DEFINITIONS
//====================================================================

void init_student(void)
{
    init_LCD();
    lcd_command(CLEAR);
    lcd_putstring("MLTKAM010");
}

void init_ADC(void)
{
    // Enable ADC clock
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

    ADC1 -> CFGR1 &= ~ADC_CFGR1_CONT;// Disable CONTinuous mode 
    ADC1 -> CFGR1 |= ADC_CFGR1_DISCEN; // Enable discontinuous mode 
    // Select ADC channel 5 (PA6)
    ADC1->CHSELR |= ADC_CHSELR_CHSEL6;
    // ADC1-> IER |= ADC_IER_E0
    // Set ADC resolution to 8-bit
    ADC1->CFGR1 |= ADC_CFGR1_RES_1;

    // Enable ADC
    ADC1->CR |= ADC_CR_ADEN;

    // Wait until ADC is ready
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);
    NVIC_EnableIRQ(ADC1_COMP_IRQn);
}

//====================================================================
// INTERRUPT SERVICE ROUTINES
//====================================================================


//********************************************************************
// END OF PROGRAM
//********************************************************************