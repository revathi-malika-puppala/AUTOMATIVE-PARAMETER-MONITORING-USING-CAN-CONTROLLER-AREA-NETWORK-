void Init_ADC(unsigned char);                 // Function prototype to initialize ADC on a given pin
void Read_ADC(int chNo, float *eAR, int *adcDval);  
// Function prototype to read ADC value from channel chNo
// Returns both digital value (adcDval) and equivalent analog voltage (eAR)

int Read_fuel(void);                          // Function prototype to read fuel level (application-specific)
