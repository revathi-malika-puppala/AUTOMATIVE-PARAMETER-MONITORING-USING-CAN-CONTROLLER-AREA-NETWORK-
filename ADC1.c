#include <LPC21xx.h>                 // Include LPC21xx microcontroller register definitions
#include "delay.h"                   // Include delay functions
#include "lcd.h"                     // Include LCD functions (optional for displaying ADC results)
#include "adc_defines.h"             // Include ADC register/bit definitions

// Initialize ADC on a given pin
void Init_ADC(unsigned char pin){
    PINSEL1 &= ~(1<<pin);            // Clear pin function bits (reset to GPIO)
    PINSEL1 |= (1<<pin);             // Configure pin as ADC input
    ADCR = ((1<<PDN_BIT) |           // Power up ADC (PDN bit = 1)
            (CLKDIV<<CLKDIV_BITS));  // Set clock divider for ADC conversion speed
}

// Read ADC value from a given channel
void Read_ADC(int chNo, float *eAR, int *adcDval){
    ADCR &= 0xFFFFFF00;              // Clear previous channel selection and start bits
    ADCR |= ((1<<START_BIT) |        // Start conversion
             (1<<chNo));             // Select ADC channel number
    delay_us(3);                     // Small delay for conversion start
    while(((ADDR >> DONE_BIT) & 1) == 0); // Wait until conversion is complete
    ADCR &= ~(1<<START_BIT);         // Stop conversion
    *adcDval = ((ADDR >> DIGITAL_CONV_DATA) & 1023); // Extract 10-bit digital ADC value
    *eAR = *adcDval * (3.3/1023);    // Convert digital value to equivalent analog voltage (0–3.3V)
}
