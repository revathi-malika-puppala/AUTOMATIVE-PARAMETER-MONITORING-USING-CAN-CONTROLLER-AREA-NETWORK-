#include<LPC21xx.h>                 // Include LPC21xx microcontroller register definitions
#include "delay.h"                  // Include delay functions

#define D 1<<17                      // Define 1-Wire data line on P0.17
#define R (IOPIN0&(1<<17))           // Macro to read the state of P0.17

/** RESET FUNCTION DEFINITION FOR DS18B20 **/
unsigned char ResetDS18b20(void)
{
    unsigned int presence; 
    IODIR0 |= D;                     // Configure P0.17 as output
    IOPIN0 |= D;                     // Drive line high
    delay_us(1);                     // Short delay (1 탎)
    IOPIN0 &= ~(D);                  // Pull line low to initiate reset pulse
    delay_us(478);                   // Hold low for ~486 탎
    IOPIN0 |= D;                     // Release line (drive high)
    delay_us(54);                    // Wait ~55 탎
    presence = IOPIN0;               // Read presence pulse
    delay_us(423);                   // Wait ~431 탎

    if(presence & R)                 // If sensor did not pull line low
        return 1;                    // Return error (no presence detected)
    else 
        return 0;                    // Return success (presence detected)
}

/** READING A BIT USING 1-WIRE PROTOCOL FROM DS18B20 **/
unsigned char ReadBit(void)
{
    unsigned int B; 
    IOPIN0 &= ~(D);                  // Pull line low to start read slot
    delay_us(1);                     // Wait 1 탎
    IOPIN0 |= D;                     // Release line
    IODIR0 &= ~(D);                  // Configure pin as input
    delay_us(10);                    // Wait ~11 탎
    B = IOPIN0;                      // Sample line state
    IODIR0 |= D;                     // Reconfigure pin as output
    if(B & R)                        // If line is high
        return 1;                    // Return bit = 1
    else 
        return 0;                    // Return bit = 0
}

/** WRITING A BIT USING 1-WIRE PROTOCOL INTO DS18B20 **/
void WriteBit(unsigned char Dbit)
{
    IOPIN0 &= ~(D);                  // Pull line low to start write slot
    delay_us(1);                     // Wait 1 탎
    if(Dbit)                         // If writing a '1'
        IOPIN0 |= D;                 // Release line early
    delay_us(58);                    // Hold for ~59 탎
    IOPIN0 |= D;                     // Ensure line is high
    delay_us(1);                     // Recovery time
}

/** READING A BYTE USING 1-WIRE PROTOCOL FROM DS18B20 **/
unsigned char ReadByte(void)
{
    unsigned char i;
    unsigned char Din = 0;
    for (i=0; i<8; i++)              // Loop through 8 bits
    {
        Din |= ReadBit() ? 0x01<<i : Din; // Read each bit and store in Din
        delay_us(45);                // Wait ~46 탎 between bits
    }
    return(Din);                     // Return assembled byte
}

/** WRITING A BYTE USING 1-WIRE PROTOCOL INTO DS18B20 **/
void WriteByte(unsigned char Dout)
{
    unsigned char i;
    for (i=0; i<8; i++)              // Loop through 8 bits
    {       
        WriteBit((Dout & 0x1));      // Write least significant bit
        Dout = Dout >> 1;            // Shift right for next bit
        delay_us(1);                 // Short delay
    }
    delay_us(98);                    // Wait ~100 탎 after byte write
}

/** READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL **/
int ReadTemp(void)
{
    unsigned char n, buff[2];
    int temp, cnt=0;

    ResetDS18b20();                  // Reset DS18B20
    WriteByte(0xcc);                 // Skip ROM command (address all devices)
    WriteByte(0x44);                 // Start temperature conversion

    while(ReadByte() == 0xff){       // Wait until conversion is complete
        cnt++;
        if(cnt == 12){               // Timeout after 12 attempts
            return -1;               // Return error
        }
    }

    ResetDS18b20();                  // Reset again
    WriteByte(0xcc);                 // Skip ROM
    WriteByte(0xbe);                 // Read scratchpad command

    for(n=0; n<2; n++)               // Read first 2 bytes (LSB + MSB)
    {
        buff[n] = ReadByte();        // Store temperature data
    }

    temp = buff[1];                  // MSB
    temp = temp << 8;                // Shift MSB to high byte
    temp = temp | buff[0];           // Combine with LSB
    return(temp);                    // Return raw temperature value
}
