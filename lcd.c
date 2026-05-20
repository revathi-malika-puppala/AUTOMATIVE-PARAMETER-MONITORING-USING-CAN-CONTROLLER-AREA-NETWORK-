#include<LPC21xx.h>                 // Include LPC21xx microcontroller register definitions
#include "delay.h"                  // Include delay functions
#include "types.h"                  // Include custom type definitions (u8, s32, f32, etc.)
#include "defines.h"                // Include bit manipulation macros
#include "lcd.h"                    // Include LCD function prototypes

#define CAT 0xff                     // Mask for LCD data lines (8 bits)
#define RS 5                         // Register Select pin (command/data control)
#define RW 7                         // Read/Write pin
#define EN 6                         // Enable pin

void Init_LCD(void){                 // Initialize LCD in 8-bit mode
    IODIR0 |= ((CAT<<8)|(1<<RS)|(1<<RW)|(1<<EN)); // Configure LCD pins as output
    delay_ms(20);                    // Wait for LCD power stabilization
    cmdLCD(0x30);                    // Function set command
    delay_ms(10);
    cmdLCD(0x30);                    // Repeat function set
    delay_ms(1);
    cmdLCD(0x30);                    // Repeat again
    delay_ms(1);
    cmdLCD(0x38);                    // Set 8-bit, 2-line, 5x7 dots
    cmdLCD(0x10);                    // Cursor move direction
    cmdLCD(0x01);                    // Clear display
    cmdLCD(0x06);                    // Entry mode set (increment cursor)
    cmdLCD(0x0C);                    // Display ON, cursor OFF
}

void cmdLCD(u8 cmd){                 // Send command to LCD
    IOCLR0 = 1<<RS;                  // RS = 0 (command mode)
    dispLCD(cmd);                    // Send command value
}

void charLCD(u8 data){               // Send character to LCD
    IOSET0 = 1<<RS;                  // RS = 1 (data mode)
    dispLCD(data);                   // Send data value
}

void dispLCD(u8 val){                // Low-level function to send data/command
    IOCLR0 = 1<<RW;                  // RW = 0 (write mode)
    WRITEBYTE(IOPIN0,8,val);         // Write 8-bit value to LCD data lines
    IOSET0 = 1<<EN;                  // Enable pulse HIGH
    delay_us(1);                     // Short delay
    IOCLR0 = 1<<EN;                  // Enable pulse LOW
    delay_ms(2);                     // Wait for LCD to process
}

void stringLCD(char *ptr){           // Display string on LCD
    while(*ptr)                      // Loop until null terminator
        charLCD(*ptr++);             // Display each character
}

void integerLCD(s32 data){           // Display integer on LCD
    u8 a[30];                        // Buffer for digits
    int i=0,n;
    if(data==0)                      // If number is zero
        charLCD('0');                // Display '0'
    if(data<0){                      // If number is negative
        data=-data;                  // Convert to positive
        charLCD('-');                // Display minus sign
    }
    while(data){                     // Extract digits
        a[i++] = (data%10)+48;       // Convert digit to ASCII
        data /= 10;
    }
    for(n=i-1;n>=0;n--)              // Display digits in correct order
        charLCD(a[n]);
}

void floatLCD(f32 f){                // Display floating-point number
    int num1=f, num2, n=0;
    f = f - num1;                    // Extract fractional part
    while(n++<6)                     // Scale fractional part
        f *= 10;
    num2 = f;
    integerLCD(num1);                // Display integer part
    charLCD('.');                    // Display decimal point
    integerLCD(num2);                // Display fractional part
}

void RIndicatorDisp(){               // Display right indicator symbol
    int i;
    char LUT[]={0x04,0x06,0x1F,0x1F,0x06,0x04,0x00,0x00}; // Custom character bitmap
    for(i=0;i<8;i++)
        charLCD(LUT[i]);             // Send bitmap to LCD
}

void LIndicatorDisp(){               // Display left indicator symbol
    int i;
    char LUT[]={0x04,0x0C,0x1F,0x1F,0x0C,0x04,0x00,0x00}; // Custom character bitmap
    for(i=0;i<8;i++)
        charLCD(LUT[i]);
}

void fuel1(){                        // Display fuel bar segment 1
    int i;
    char LUT[]={0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00}; // Custom character bitmap
    for(i=0;i<8;i++)
        charLCD(LUT[i]);
}

void fuel2(){                        // Display fuel bar segment 2
    int i;
    char LUT[]={0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00}; // Custom character bitmap
    for(i=0;i<8;i++)
        charLCD(LUT[i]);
}

void fuel3(){                        // Display fuel bar segment 3
    int i;
    char LUT[]={0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00}; // Custom character bitmap
    for(i=0;i<8;i++)
        charLCD(LUT[i]);
}

void fuel4(){                        // Display fuel bar segment 4
    int i;
    char LUT[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00}; // Custom character bitmap
    for(i=0;i<8;i++)
        charLCD(LUT[i]);
}
