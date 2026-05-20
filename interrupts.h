#define EINT0_PIN        16   // Define external interrupt 0 pin number (P0.16 on LPC21xx)
#define EINT0_VIC_CHNO   14   // Define VIC (Vector Interrupt Controller) channel number for EINT0

#define EINT1_PIN        3    // Define external interrupt 1 pin number (P0.3 on LPC21xx)
#define EINT1_VIC_CHNO   15   // Define VIC channel number for EINT1

void Enable_EINTs(void);      // Function prototype to enable and configure external interrupts (EINT0, EINT1)
