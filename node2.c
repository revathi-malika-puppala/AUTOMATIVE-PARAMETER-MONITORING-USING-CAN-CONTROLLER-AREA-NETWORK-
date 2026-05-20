#include <LPC21xx.h>          // Include LPC21xx microcontroller register definitions
#include "delay.h"            // Include delay functions
#include "can.h"              // Include CAN communication functions and structures

CANF rxF;                     // Define CAN frame structure for receiving data

int main(){
    unsigned char n;          // Variable used for LED shifting pattern
    Init_CAN1();              // Initialize CAN1 controller
    IODIR0 |= 0xFF;           // Configure P0.0–P0.7 as output (LEDs)
    IOSET0 = 0xFF;            // Turn ON all LEDs initially

    while(1){                 // Infinite loop for continuous monitoring
        if(C1GSR & 0x01){     // Check if CAN1 receive buffer has data
            CAN1_Rx(&rxF);    // Receive CAN frame into rxF
            C1CMR = (0x04);   // Release receive buffer

            if(rxF.ID == 1){  // If received CAN frame ID is 1
                if(rxF.Data1 == 1){   // If Data1 = 1 (left indicator pattern)
                    while(1){
                        n = 0x01;     // Start with LED at position 0 (LSB)
                        while(n){
                            IOCLR0 = n;       // Clear (turn OFF) LED at position n
                            delay_ms(200);    // Delay for visible blink
                            n = n << 1;       // Shift LED to the left
                            if(C1GSR & 1){    // Check for new CAN frame
                                CAN1_Rx(&rxF);
                                if(rxF.ID == 1)
                                    if(rxF.Data1 != 1) // If Data1 changes, break loop
                                        break;
                            }
                        }
                        IOSET0 = 0xFF;        // Turn ON all LEDs
                        delay_ms(200);        // Delay before next cycle
                        if(rxF.ID == 1)
                            if(rxF.Data1 != 1) // Exit if Data1 changes
                                break;
                    }
                }else if(rxF.Data1 == 2){     // If Data1 = 2 (right indicator pattern)
                    while(1){
                        n = 0x80;             // Start with LED at position 7 (MSB)
                        while(n){
                            IOCLR0 = n;       // Clear (turn OFF) LED at position n
                            delay_ms(200);    // Delay for visible blink
                            n = n >> 1;       // Shift LED to the right
                            if(C1GSR & 1){    // Check for new CAN frame
                                CAN1_Rx(&rxF);
                                if(rxF.ID == 1)
                                    if(rxF.Data1 != 2) // If Data1 changes, break loop
                                        break;
                            }
                        }
                        IOSET0 = 0xFF;        // Turn ON all LEDs
                        delay_ms(200);        // Delay before next cycle
                        if(rxF.ID == 1)
                            if(rxF.Data1 != 2) // Exit if Data1 changes
                                break;
                    }
                }else{                        // If Data1 is neither 1 nor 2
                    IOSET0 = 0xFF;            // Keep all LEDs ON
                }
            }
        }
    }
}
