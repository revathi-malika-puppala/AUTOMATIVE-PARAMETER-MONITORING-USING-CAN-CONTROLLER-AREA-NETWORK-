#include <LPC21xx.h>                 // Include LPC21xx microcontroller register definitions
#include "adc.h"                     // Include ADC initialization and read functions
#include "adc_defines.h"             // Include ADC configuration constants
#include "delay.h"                   // Include delay functions
#include "can.h"                     // Include CAN communication functions
#include "lcd.h"                     // Include LCD functions (optional for displaying fuel level)

int adcDval;                         // Variable to store raw ADC digital value
float eAR;                           // Variable to store equivalent analog voltage

CANF txF;                            // CAN frame structure for transmitting fuel data
volatile int t;                      // Variable to store fuel percentage

int main(){
    Init_CAN1();                     // Initialize CAN1 controller
    Init_ADC(AIN1_0_27);             // Initialize ADC on channel AIN1 (P0.27)

    txF.ID = 2;                      // Set CAN frame ID = 2 (fuel data)
    txF.bfv.RTR = 0;                 // Data frame (not remote frame)
    txF.bfv.DLC = 1;                 // Data length = 1 byte

    while(1){                        // Infinite loop for continuous monitoring
        Read_ADC(1, &eAR, &adcDval); // Read ADC channel 1 ? get voltage and digital value

        // Clamp ADC value within defined thresholds
        if(adcDval > MAX_VAL)
            adcDval = MAX_VAL;
        else if(adcDval < MIN_VAL)
            adcDval = MIN_VAL;

        // Convert ADC value to percentage (0–100%)
        t = (((adcDval - MIN_VAL) * 100) / (MAX_VAL - MIN_VAL));    

        txF.Data1 = t;               // Store fuel percentage in CAN frame
        CAN1_Tx(txF);                // Transmit CAN frame with fuel data

        delay_ms(500);               // Delay before next reading/transmission
    }
}
