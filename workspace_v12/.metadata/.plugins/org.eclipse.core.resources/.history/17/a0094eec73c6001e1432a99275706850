#include <msp430.h>

// Assume using P1.6 for PWM, adjust as per your actual pin configuration
#define PWM_PIN BIT6

void initializePWM(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    // Configure the GPIO pin for PWM function
    P1DIR |= PWM_PIN;           // Set PWM pin as output
    P1SEL0 |= PWM_PIN;          // Select PWM function for the pin (consult datasheet for correct SEL register)

    // Configure Timer_B
    TB0CTL = TBSSEL__SMCLK + MC__UP; // SMCLK, Up mode
    TB0CCR0 = 1000 - 1;              // Set maximum count value (PWM period)
    TB0CCR1 = 0;                     // Start with a duty cycle of 0%
    TB0CCTL1 = OUTMOD_7;             // Reset/Set mode for PWM

    // Ensure SMCLK is configured to the desired frequency for your PWM
}

void setFanSpeed(unsigned int speed) {
    // Speed is a value between 0 and 1000, where 1000 corresponds to 100% duty cycle
    if (speed <= 1000) {
        TB0CCR1 = speed; // Adjust the PWM duty cycle
    }
}

int main(void) {
    initializePWM();

    // Example usage
    while (1) {
        setFanSpeed(500); // Set to 50% duty cycle
        __delay_cycles(1000000); // Simple delay, adjust as necessary
        setFanSpeed(250); // Set to 25% duty cycle
        __delay_cycles(1000000); // Simple delay, adjust as necessary
    }
}

