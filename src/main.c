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
void init_GPIOB(void);
void init_GPIOA(void);
uint8_t ADC_read(void);

//====================================================================
// MAIN FUNCTION
//====================================================================

int main (void)
{
    init_student();
    init_GPIOA();
    init_GPIOB();
    init_ADC();
    uint8_t ADC_read();
    uint8_t adc_result = 0;
    while (1)
    {
        //================ ADC READ =================
        adc_result = ADC_read();

        //================ LED OUTPUT ================
        GPIOB->ODR = adc_result;   // show binary on LEDs

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
uint8_t ADC_read(void)
{
    // Start conversion
    ADC1->CR |= ADC_CR_ADSTART;

    // Wait until conversion is complete
    while ((ADC1->ISR & ADC_ISR_EOC) == 0);

    // Return ADC result (0–255)
    return ADC1->DR;
}
//================ GPIOA INIT (PA5 = ADC INPUT) =====================
void init_GPIOA(void)
{
    // Enable clock for GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Set PA5 to ANALOG mode (11)
    GPIOA->MODER |= GPIO_MODER_MODER6;
}

//================ GPIOB INIT (LED OUTPUTS) ==========================
void init_GPIOB(void)
{
    // Enable clock for GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // Set PB0–PB7 as output pins
    GPIOB->MODER |= GPIO_MODER_MODER0_0;   // PB0 to output
    GPIOB->MODER |= GPIO_MODER_MODER1_0;   // PB1 to output
    GPIOB->MODER |= GPIO_MODER_MODER2_0;   // PB2 to output
    GPIOB->MODER |= GPIO_MODER_MODER3_0;   // PB3 to output
    GPIOB->MODER |= GPIO_MODER_MODER4_0;   // PB4 to output
    GPIOB->MODER |= GPIO_MODER_MODER5_0;   // PB5 to output
    GPIOB->MODER |= GPIO_MODER_MODER6_0;   // PB6 to output
    GPIOB->MODER |= GPIO_MODER_MODER7_0;   // PB7 to output
}

//====================================================================
// INTERRUPT SERVICE ROUTINES
//====================================================================


//********************************************************************
// END OF PROGRAM
//********************************************************************