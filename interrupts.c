#include <LPC21xx.h>                 // Include LPC21xx microcontroller register definitions
#include "interrupts.h"              // Include interrupt configuration header

volatile int flag1 = 1;              // Flag to control left indicator state
volatile int flag2 = 1;              // Flag to control right indicator state

volatile int blinkright;             // Variable to track right indicator blinking
volatile int blinkleft;              // Variable to track left indicator blinking

// External Interrupt 0 ISR (handles left indicator)
void eint0_isr(void) __irq
{
    if(flag1){                       // If left indicator is enabled
        blinkleft = 1;               // Turn ON left indicator blinking
        blinkright = 0;              // Ensure right indicator is OFF
        flag1 = 0;                   // Reset left flag
        flag2 = 1;                   // Reset right flag
    }else{                           // If left indicator is disabled
        blinkright = 0;              // Turn OFF right indicator
        blinkleft = 0;               // Turn OFF left indicator
        flag1 = 1;                   // Reset flags
        flag2 = 1;
    }
    EXTINT = 1<<0;                   // Clear EINT0 interrupt flag
    VICVectAddr = 0;                 // Acknowledge interrupt to VIC
}

// External Interrupt 1 ISR (handles right indicator)
void eint1_isr(void) __irq
{
    if(flag2){                       // If right indicator is enabled
        blinkright = 1;              // Turn ON right indicator blinking
        blinkleft = 0;               // Ensure left indicator is OFF
        flag2 = 0;                   // Reset right flag
        flag1 = 1;                   // Reset left flag
    }else{                           // If right indicator is disabled
        blinkright = 0;              // Turn OFF right indicator
        blinkleft = 0;               // Turn OFF left indicator
        flag2 = 1;                   // Reset flags
        flag1 = 1;
    }
    EXTINT = 1<<1;                   // Clear EINT1 interrupt flag
    VICVectAddr = 0;                 // Acknowledge interrupt to VIC
}

// Function to enable and configure external interrupts
void Enable_EINTs(void){
    PINSEL0 = ((PINSEL0 & ~(3<<6)) | (3<<6));   // Configure P0.3 as EINT1
    PINSEL1 = ((PINSEL1 & ~(3<<0)) | (1<<0));   // Configure P0.16 as EINT0

    VICIntEnable = ((1<<EINT0_VIC_CHNO) |       // Enable EINT0 interrupt in VIC
                    (1<<EINT1_VIC_CHNO));       // Enable EINT1 interrupt in VIC

    VICVectCntl0 = (1<<5) | EINT0_VIC_CHNO;     // Assign ISR to VIC slot 0 for EINT0
    VICVectAddr0 = (unsigned int) eint0_isr;    // Set ISR address for EINT0

    VICVectCntl1 = (1<<5) | EINT1_VIC_CHNO;     // Assign ISR to VIC slot 1 for EINT1
    VICVectAddr1 = (unsigned int) eint1_isr;    // Set ISR address for EINT1

    EXTMODE = ((1<<0) | (1<<1));                // Configure EINT0 and EINT1 as edge-triggered
}
