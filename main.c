#include<LPC21xx.h>          // Include header file for LPC21xx microcontroller definitions
#include "lcd.h"             // Include custom header for LCD functions
#include "delay.h"           // Include custom header for delay functions
#include "types.h"           // Include custom header for type definitions
#include "defines.h"         // Include custom header for constant definitions
#include "can.h"             // Include custom header for CAN communication functions
#include "ds18b20.h"         // Include custom header for DS18B20 temperature sensor functions
#include "interrupts.h"      // Include custom header for interrupt handling

CANF txF;                    // Define CAN frame structure for transmission
CANF rxF;                    // Define CAN frame structure for reception

extern int blinkleft;        // External variable indicating left indicator blinking
extern int blinkright;       // External variable indicating right indicator blinking

int main(){                  // Main function begins
    int temp,fuel=0;         // Declare variables: temp for temperature, fuel for fuel level
    
    Init_CAN1();             // Initialize CAN1 module
    Init_LCD();              // Initialize LCD display
    delay_s(1);              // Delay for 1 second
    Enable_EINTs();          // Enable external interrupts
    
    txF.ID=1;                // Set CAN frame ID to 1
    txF.bfv.RTR=0;           // Set Remote Transmission Request bit to 0 (data frame)
    txF.bfv.DLC=1;           // Set Data Length Code to 1 (1 byte of data)

    while(1){                // Infinite loop for continuous monitoring
        cmdLCD(0x80);        // Set LCD cursor to first line
        stringLCD("Parameter Monitoring"); // Display title on LCD
        
        cmdLCD(0x94);        // Set LCD cursor to second line
        stringLCD("TEMPERATURE:"); // Display label for temperature
        
        temp=ReadTemp();     // Read temperature from DS18B20 sensor
        if(temp==-1){        // If sensor returns error
            stringLCD("TEMP ERR"); // Display error message
        }else{               // Otherwise display temperature value
            integerLCD(temp>>4); // Convert raw sensor value to Celsius and display
            charLCD(223);        // Display degree symbol
            stringLCD("C    ");  // Display unit 'C' and clear extra spaces
        }
        
        cmdLCD(0xD4);        // Set LCD cursor to third line
        stringLCD("INDICATOR:"); // Display label for indicators
        
        cmdLCD(0x48);        // Set cursor position for left indicator
        LIndicatorDisp();    // Display left indicator status
        
        cmdLCD(0x40);        // Set cursor position for right indicator
        RIndicatorDisp();    // Display right indicator status
        
        cmdLCD(0xD4+11);     // Set cursor position for left indicator symbol
        charLCD(1);          // Display custom character for left indicator
        
        cmdLCD(0xD4+13);     // Set cursor position for right indicator symbol
        charLCD(0);          // Display custom character for right indicator
        
        cmdLCD(0x50);        // Set cursor position for fuel bar 1
        fuel1();             // Display fuel bar segment 1
        
        cmdLCD(0x58);        // Set cursor position for fuel bar 2
        fuel2();             // Display fuel bar segment 2
        
        cmdLCD(0x60);        // Set cursor position for fuel bar 3
        fuel3();             // Display fuel bar segment 3
        
        cmdLCD(0x68);        // Set cursor position for fuel bar 4
        fuel4();             // Display fuel bar segment 4
        
        if(blinkleft){       // If left indicator is blinking
            txF.Data1=1;     // Set CAN data to 1 (left indicator ON)
            CAN1_Tx(txF);    // Transmit CAN frame
            cmdLCD(0xD4+11); // Set cursor for left indicator symbol
            charLCD(1);      // Display left indicator symbol
            delay_ms(500);   // Delay for blink effect
            cmdLCD(0xD4+11); // Clear symbol
            charLCD(' ');
            delay_ms(500);   // Delay for blink effect
        }else if(blinkright){ // If right indicator is blinking
            txF.Data1=2;     // Set CAN data to 2 (right indicator ON)
            CAN1_Tx(txF);    // Transmit CAN frame
            cmdLCD(0xD4+13); // Set cursor for right indicator symbol
            charLCD(0);      // Display right indicator symbol
            delay_ms(500);   // Delay for blink effect
            cmdLCD(0xD4+13); // Clear symbol
            charLCD(' ');
            delay_ms(500);   // Delay for blink effect
        }else{               // If no indicator is blinking
            txF.Data1=3;     // Set CAN data to 3 (no indicator)
            CAN1_Tx(txF);    // Transmit CAN frame
        }
        
        if(C1GSR&1){         // If CAN1 receive buffer has data
            CAN1_Rx(&rxF);   // Receive CAN frame into rxF
            if(rxF.ID == 2) { // If received frame ID is 2 (fuel data)
                fuel=rxF.Data1; // Store fuel level from CAN data
            }
        }
        
        cmdLCD(0xC0);        // Set LCD cursor to fourth line
        stringLCD("FUEL:");   // Display fuel label
        
        if(fuel<=25){         // If fuel level is 25% or less
            charLCD(2);       // Display empty fuel bar
            charLCD(' ');
            charLCD(' ');
            charLCD(' ');
        }
        else if(fuel<=50){    // If fuel level is up to 50%
            charLCD(2);       // Display first bar
            charLCD(3);       // Display second bar
            charLCD(' ');
            charLCD(' ');
        }
        else if(fuel<=75){    // If fuel level is up to 75%
            charLCD(2);       // Display first bar
            charLCD(3);       // Display second bar
            charLCD(4);       // Display third bar
            charLCD(' ');
        }else{                // If fuel level is above 75%
            charLCD(2);       // Display first bar
            charLCD(3);       // Display second bar
            charLCD(4);       // Display third bar
            charLCD(5);       // Display fourth bar (full)
        }
        
        cmdLCD(0xC9);         // Set cursor position for fuel percentage
        integerLCD(fuel);     // Display numeric fuel percentage
        stringLCD("%  ");     // Display '%' symbol and clear extra spaces
        
        delay_ms(10);         // Small delay for stability
    }
}
