#include <msp430.h>
#include <driverlib.h>
#include <Board.h>
//#include <lcd.h>


// Define ADC input channel for P1.7 (ADC7)
#define ADC_INPUT_CHANNEL ADCINCH_7
#define LOAD_RESISTANCE 100.0 // Define load resistance value in ohms

void initADC(void) {
    // Configure P1.7 for ADC input
    P1SEL0 |= BIT7; // Corrected from PASEL0_L to P1SEL0
    P1SEL1 |= BIT7; // Corrected from PASEL1_L to P1SEL1


    // Initialize ADC
    ADCCTL0 = ADCSHT_2 + ADCON; // ADC ON, Sampling time
    ADCCTL1 = ADCSHP; // ADC clock source = sampling timer
    ADCCTL2 = ADCRES_2; // 12-bit conversion results
    ADCMCTL0 = ADC_INPUT_CHANNEL; // Configure ADC input channel

    ADCIE = ADCIE0; // Enable ADC conversion complete interrupt
    __enable_interrupt(); // Enable global interrupts
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    initADC(); // Initialize ADC for voltage measurement
    lcd_init(); // Initialize your LCD

    while(1) {
        ADCCTL0 |= ADCENC | ADCSC; // Start sampling and conversion

        __bis_SR_register(LPM0_bits + GIE); // Enter LPM0, ADC_ISR will force exit

        // ADCMEM0 contains the converted value once ADC conversion is complete
        float voltage = (ADCMEM0 * 3.3) / 4095; // Convert ADC value to voltage assuming 3.3V reference
        float power = (voltage * voltage) / LOAD_RESISTANCE; // P=V^2/R

        lcd_clear(); // Clear LCD display
        lcd_print_power(power); // Function to display power, needs to be defined according to your LCD
    }
}

// ADC interrupt service routine
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG)) {
        case ADCIV_ADCIFG: // When conversion is complete
            __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
            break;
        default: break;
    }
}

// Placeholder for lcd_print_power function - implement according to your LCD specs
//void lcd_print_power(float power) {
    // Example: Convert power to string and print
    //char powerStr[16];
    //sprintf(powerStr, "Power: %.2fW", power);
   // lcd_print(powerStr);
//}





