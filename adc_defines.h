#define FOSC    12000000             // Oscillator frequency (12 MHz)
#define CCLK    (FOSC*5)             // CPU clock frequency (multiplier = 5 ? 60 MHz)
#define PCLK    (CCLK/4)             // Peripheral clock frequency (CCLK/4 ? 15 MHz)
#define ADCCLK  3000000              // Desired ADC clock frequency (3 MHz)
#define CLKDIV  ((PCLK/ADCCLK)-1)    // Clock divider value for ADC (prescaler calculation)

#define CLKDIV_BITS 8                // Bit position for CLKDIV in ADCR register
#define PDN_BIT     21               // Power-down bit (set to 1 to enable ADC)
#define START_BIT   24               // Start conversion bit

#define DIGITAL_CONV_DATA 6          // Bit position of ADC result data in ADDR register
#define DONE_BIT          31         // Bit position indicating conversion complete

#define AIN1_0_27 24                 // Pin function select value for ADC channel 1 (P0.27)

#define MAX_VAL  340                 // Maximum threshold value (application-specific)
#define MIN_VAL  90                  // Minimum threshold value (application-specific)
