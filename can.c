// can.c - Source file for CAN (Controller Area Network) communication functions

#include <LPC21xx.h>          // Include LPC21xx microcontroller register definitions
#include "types.h"            // Include custom type definitions (u32, etc.)
#include "delay.h"            // Include delay functions
#include "can_defines.h"      // Include CAN controller register/bit definitions
#include "can.h"              // Include CAN frame structure and function prototypes
// #include "pin_connect_block.h" // Optional include for pin configuration (commented out)

void Init_CAN1(void)
{
    // Configure P0.25 as CAN1_RX pin (RD1)
    PINSEL1 = (1 << ((25 - 16) * 2));
    // Alternative function call (commented out): configure pin using helper function
    // CfgPortPinFunc(0,25,RD1_PIN_0_25);

    // Reset CAN1 controller (set Reset Mode bit)
    C1MOD |= 1 << RM_BIT;       

    // Accept all received messages (disable acceptance filtering)
    AFMR &= ~(1 << AccOFF_BIT);   // Clear Acceptance Filter OFF bit
    AFMR |= (1 << AccBP_BIT);     // Enable bypass mode

    // Set baud rate for CAN communication
    C1BTR = BTR_LVAL;

    // Enable CAN1 controller (clear Reset Mode bit)
    C1MOD &= ~(1 << RM_BIT);                    
}

void CAN1_Tx(CANF txF)
{       
   // Wait until TX buffer 1 is empty
   while(((C1GSR >> TBS1_BIT) & 1) == 0);

   // Configure Transmit ID
   C1TID1 = txF.ID;

   // Configure RTR (Remote Transmission Request) and DLC (Data Length Code)
   C1TFI1 = ((txF.bfv.RTR << RTR_BIT) |
             (txF.bfv.DLC << DLC_BITS));

   // Check whether frame is Data Frame or Remote Frame
   if(txF.bfv.RTR != 1)
   {    
     // If Data Frame, write to transmit data buffers
     C1TDA1 = txF.Data1;   // Load bytes 1–4
     C1TDB1 = txF.Data2;   // Load bytes 5–8
   }

   // Select TX Buffer 1 and start transmission
   C1CMR |= ((1 << STB1_BIT) | (1 << TR_BIT));

   // Wait until transmission is complete
   while(((C1GSR >> TCS1_BIT) & 1) == 0); 
}

void CAN1_Rx(CANF *rxF)
{
  // Wait until a CAN frame is received (Receive Buffer Status bit set)
  while(((C1GSR >> RBS_BIT) & 1) == 0);

  // Read 11-bit CAN ID of received frame
  rxF->ID = C1RID; 

  // Read and extract Data/Remote Frame status
  rxF->bfv.RTR = ((C1RFS >> RTR_BIT) & 1);

  // Extract Data Length Code (DLC)
  rxF->bfv.DLC = ((C1RFS >> DLC_BITS) & 15);

  // If received frame is a Data Frame
  if(rxF->bfv.RTR == 0)
  { 
    // Extract data bytes 1–4
    rxF->Data1 = C1RDA;
    // Extract data bytes 5–8
    rxF->Data2 = C1RDB;
  }

  // Release receive buffer (clear RBS bit)
  C1CMR |= (1 << RRB_BIT);    
}
