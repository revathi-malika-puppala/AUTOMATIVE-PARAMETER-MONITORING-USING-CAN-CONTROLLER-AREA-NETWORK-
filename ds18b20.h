#ifndef _DS18B20_H_                 // Header guard start: prevents multiple inclusion of this file
#define _DS18B20_H_

/** DS18B20 FUNCTION DECLARATIONS **/

unsigned char ResetDS1820(void);    // Reset the DS18B20 sensor and check for presence pulse
unsigned char ReadBit(void);        // Read a single bit from the DS18B20 sensor
void WriteBit(unsigned char);       // Write a single bit to the DS18B20 sensor
unsigned char ReadByte(void);       // Read one byte (8 bits) from the DS18B20 sensor
void WriteByte(unsigned char);      // Write one byte (8 bits) to the DS18B20 sensor
int ReadTemp(void);                 // Read temperature value from DS18B20 sensor (returns integer value)

#endif                              // End of header guard
