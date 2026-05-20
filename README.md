This project implements a vehicle parameter monitoring and control system using the LPC21xx ARM7 microcontroller. It integrates multiple peripherals and modules:
>CAN bus communication for inter‑module data exchange.

>LCD display driver for visual feedback (indicators, fuel level, temperature).

>ADC interface for analog fuel sensor input.

>DS18B20 temperature sensor driver using 1‑Wire protocol.

>External interrupts for left/right indicator control.

>Delay utilities for timing operations.

The system simulates a vehicle dashboard where fuel level, temperature, and indicators are monitored and displayed, while data is exchanged over CAN.

#FEATURES

CAN Communication
>Transmit and receive CAN frames (CAN1_Tx, CAN1_Rx).

>ID‑based message handling (e.g., ID=1 for indicators, ID=2 for fuel data).

>LCD Driver.

>8‑bit mode initialization and command/data functions.

>Display strings, integers, floats.

>Custom characters for fuel bars and indicator arrows.

ADC Interface
>10‑bit resolution (0–1023).

>Converts analog fuel sensor voltage to percentage.

>Threshold clamping (MIN_VAL, MAX_VAL) for stable readings.

DS18B20 Sensor
>1‑Wire protocol implementation (reset, read/write bit, read/write byte).

>Temperature conversion and raw data retrieval.

Interrupts
>External interrupts (EINT0, EINT1) for left/right indicator toggling.

>Edge‑triggered mode for button press simulation.

Delay Utilities
>Software delays in microseconds, milliseconds, and seconds.

>Used for timing LCD pulses, CAN transmission, and LED blinking.

#SYSTEM WORKFLOW

Fuel Monitoring
>ADC reads fuel sensor voltage (P0.27).

>Value is scaled to percentage.

>CAN transmits fuel percentage (ID=2).

>LCD displays fuel bar (fuel1–fuel4).

Temperature Monitoring
>DS18B20 sensor provides raw temperature data.

>Value can be displayed on LCD or transmitted via CAN.

Indicator Control
>External interrupts simulate button presses.

>Left/right indicator blinking patterns are shown on LEDs and LCD.

>CAN messages (ID=1) synchronize indicator states.


 **can.h / can.c**  - CAN frame structure and Tx/Rx functions
 
 **can_defines.h**  -CAN register/bit definitions.
 
 **lcd.c / lcd.h**   -LCD driver functions and custom characters.
 
 **adc.c / adc.h / adc_defines.h** - ADC initialization, read functions, and constants.
 
 **ds18b20.c / ds18b20.h**  - DS18B20 sensor driver (1‑Wire protocol).
 
 **interrupts.c / interrupts.h** - External interrupt ISRs for indicators.
 
 **delay.c / delay.h** - Software delay functions.
 
 **main.c**  -Application logic (fuel monitoring, CAN transmission).

#FUTURE ENHANCEMENTS
>Integrate speed sensor via ADC or external input.

>Add CAN message filtering for selective communication.

>Implement real‑time clock (RTC) for timestamped data logging.

>Expand LCD interface to show combined dashboard (fuel + temp + indicators).
