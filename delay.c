#include "types.h"                  // Include custom type definitions (u32, etc.)

void delay_us(u32 tdly){            // Function to generate delay in microseconds
    tdly *= 12;                     // Scale input value to approximate microsecond delay (depends on CPU clock)
    while(tdly--);                  // Busy-wait loop until counter reaches zero
}

void delay_ms(u32 tdly){            // Function to generate delay in milliseconds
    tdly *= 12000;                  // Scale input value to approximate millisecond delay
    while(tdly--);                  // Busy-wait loop until counter reaches zero
} 

void delay_s(u32 tdly){             // Function to generate delay in seconds
    tdly *= 12000000;               // Scale input value to approximate second delay
    while(tdly--);                  // Busy-wait loop until counter reaches zero
}
