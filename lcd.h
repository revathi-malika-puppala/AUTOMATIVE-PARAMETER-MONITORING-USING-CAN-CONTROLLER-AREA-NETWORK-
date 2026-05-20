#include"types.h"              // Include custom type definitions (u8, s32, f32, etc.)

void Init_LCD(void);           // Function prototype to initialize the LCD module
void dispLCD(u8);              // Function prototype to display raw data/character on LCD
void charLCD(u8);              // Function prototype to display a single character on LCD
void cmdLCD(u8);               // Function prototype to send a command instruction to LCD
void stringLCD(char *);        // Function prototype to display a string on LCD
void integerLCD(s32);          // Function prototype to display an integer value on LCD
void floatLCD(f32);            // Function prototype to display a floating-point value on LCD
void LIndicatorDisp(void);     // Function prototype to display left indicator symbol/status
void RIndicatorDisp(void);     // Function prototype to display right indicator symbol/status
void fuel1(void);              // Function prototype to display first fuel bar segment
void fuel2(void);              // Function prototype to display second fuel bar segment
void fuel3(void);              // Function prototype to display third fuel bar segment
void fuel4(void);              // Function prototype to display fourth fuel bar segment
