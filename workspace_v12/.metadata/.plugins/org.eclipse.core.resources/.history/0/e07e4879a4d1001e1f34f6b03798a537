#include <msp430.h>
#include <driverlib.h>
#include <Board.h>



void setupPWM() {
    // Example assumes PWM output on a pin like P1.2. Adjust according to your actual setup.
    P1DIR |= BIT2; // Set pin as output - adjust BIT2 according to your PWM output pin
    // Assuming using TA0.1 for PWM, adjust based on your timer and channel
    TA0CCTL1 = OUTMOD_7; // Reset/Set mode
    TA0CTL = TASSEL_2 + MC_1; // SMCLK, Up mode
    TA0CCR0 = 1000 - 1; // PWM Period
    TA0CCR1 = 500; // PWM Duty Cycle 50%, adjust for initial speed

    // Enable PWM output on the correct pin, adjusting for your MSP430 model and desired output pin
    // This often involves setting a pin selection register to connect the timer output to the pin
    // For example, if using P1.2 and the specific MSP430 model uses PxSEL register:
    // P1SEL |= BIT2; // Uncomment and adjust this line according to your model and pin
}

void setFanSpeed(unsigned int speed) {
    if (speed > 100) speed = 100;
    TA0CCR1 = (TA0CCR0 + 1) * speed / 100 - 1;
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    setupPWM(); // Setup PWM

    unsigned int speed = 0; // Ensure speed is declared and initialized before the loop
    while(1) {
        for(speed = 0; speed <= 100; speed += 10) {
            setFanSpeed(speed); // Set fan speed
            __delay_cycles(1000000); // Delay to observe change
        }
    }
}



