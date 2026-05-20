#include "types.h"                  // Include custom type definitions (u32, etc.)

// TD1 CAN1_TX pin has no alternate function, defaults to GPIO
#define TD1_PIN                      // Placeholder definition for CAN1_TX pin

// Define P0.25 as RD1 (CAN1_RX) using alternate function 2
#define PIN_FUNC2      1             // Alternate function 2 value
#define RD1_PIN_0_25   PIN_FUNC2     // Assign P0.25 as CAN1_RX pin

// Clock and baud rate configuration
#define PCLK          15000000       // Peripheral clock frequency in Hz (15 MHz)
#define BIT_RATE      125000         // Desired CAN bit rate in Hz (125 kbps)
#define QUANTA        15             // Number of time quanta per bit
#define BRP           (PCLK/(BIT_RATE*QUANTA))   // Baud Rate Prescaler calculation

// Sample point configuration
#define SAMPLE_POINT  (0.7 * QUANTA) // Sample point at 70% of bit time
#define TSEG1         ((u32)SAMPLE_POINT-1)      // Time segment 1 (propagation + phase segment 1)
#define TSEG2         (QUANTA-(1+TSEG1))         // Time segment 2 (phase segment 2)
#define SJW           ((TSEG2>=5)?4:(TSEG2-1))   // Synchronization Jump Width (max 4 or TSEG2-1)

// Configuration values for CAN Bit Timing Register (CxBTR)
#define SAM         0                // Sampling mode: 0 = once, 1 = three times
#define BTR_LVAL    (SAM<<23 |       \
                     ((TSEG2-1)<<20)|\
                     ((TSEG1-1)<<16)|\
                     ((SJW-1)<<14)|  \
                     (BRP-1))        // Construct BTR value with timing parameters

// CxCMR (Command Register) bit definitions
#define TR_BIT      0                // Transmission Request bit
#define RRB_BIT     2                // Release Receive Buffer bit
#define STB1_BIT    5                // Select Transmit Buffer 1 bit

// CxGSR (Global Status Register) bit definitions
#define RBS_BIT     0                // Receive Buffer Status bit
#define TBS1_BIT    2                // Transmit Buffer 1 Status bit
#define TCS1_BIT    3                // Transmission Complete Status bit

// CxTFI1 / CxRFS (Frame Info Registers) bit definitions
#define FF_BIT      31               // Frame Format bit (0 = standard, 1 = extended)
#define RTR_BIT     30               // Remote Transmission Request bit
#define DLC_BITS    16               // Data Length Code bits (4 bits wide)

// CxMOD (Mode Register) bit definitions
#define RM_BIT      0                // Reset Mode bit

// AFMR (Acceptance Filter Mode Register) bit definitions
#define AccOFF_BIT  0                // Acceptance Filter OFF bit
#define AccBP_BIT   1                // Acceptance Filter Bypass bit
