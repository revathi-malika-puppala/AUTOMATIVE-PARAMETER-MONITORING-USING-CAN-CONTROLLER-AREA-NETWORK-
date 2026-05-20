// can.h - Header file for CAN (Controller Area Network) communication functions

#include "types.h"                // Include custom type definitions (u32, etc.)

// Define a structure to represent a CAN frame
typedef struct CAN_Frame
{   
    u32 ID;                       // CAN identifier (message ID)

    // Bitfield structure for frame control
    struct BitField
    {
        // u32 FF  : 1;          // (Optional) Frame Format bit, commented out
        u32 RTR : 1;            // Remote Transmission Request bit (0 = data frame, 1 = remote frame)
        u32 DLC : 4;            // Data Length Code (number of data bytes, 0–8)
    }bfv;   
    
    u32 Data1, Data2;             // Data fields (payload of the CAN frame)
}CANF;                            // Typedef alias CANF for easier usage

// Function prototypes for CAN operations
void Init_CAN1(void);             // Initialize CAN1 controller
void CAN1_Tx(CANF txF);           // Transmit a CAN frame (txF) via CAN1
void CAN1_Rx(CANF *rxF);          // Receive a CAN frame into rxF via CAN1
