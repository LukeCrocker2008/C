/*------------------------------------------------------------------------------
 * File:        Lab11_D2.c (CPE 325 Lab11 Demo code)
 * Function:    Interfacing thumbstick (MPS430FG4618)
 * Description: This C program interfaces with a thumbstick sensor that has
 *              x (HORZ) and y (VERT) axis and outputs from 0 to 3V.
 *              The value of x and y axis
 *              is sent as the percentage of power to the UAH Serial App.
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal between XIN & XOUT is required for ACLK
 *
 *                         MSP430xG461x
 *                      -------------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |     P2.4/UCA0TXD|------------>
 *                      |                 | 38400 - 8N1
 *                      |     P2.5/UCA0RXD|<------------
 *                      |                 |
 * Input:       Connect thumbstick to the board
 * Output:      Displays % of power in UAH serial app
 * Author:      Micah Harvey
 *------------------------------------------------------------------------------*/


#define Xper (ADC12MEM0*3.0/4095*100/3)
#define Yper (ADC12MEM1*3.0/4095*100/3)

void TimerA_setup(void) {
    TACCR0 = 3277;                      // 3277 / 32768 Hz = 0.1s
    TACTL = TASSEL_1 + MC_1;            // ACLK, up mode
    TACCTL0 = CCIE;                     // Enabled interrupt
}

void ADC_setup(void) {
    int i =0;

    P6DIR &= ~BIT3 + ~BIT7;             // Configure P6.3 and P6.7 as input pins
    P6SEL |= BIT3 + BIT7;               // Configure P6.3 and P6.7 as analog pins
    ADC12CTL0 = ADC12ON + SHT0_6 + MSC; // configure ADC converter
    ADC12CTL1 = SHP + CONSEQ_1;         // Use sample timer, single sequence
    ADC12MCTL0 = INCH_3;                // ADC A3 pin - Stick X-axis
    ADC12MCTL1 = INCH_7 + EOS;          // ADC A7 pin - Stick Y-axis
                                        // EOS - End of Sequence for Conversions
    ADC12IE |= 0x04;                    // Enable ADC12IFG.1
    for (i = 0; i < 0x3600; i++);       // Delay for reference start-up
    ADC12CTL0 |= ENC;                   // Enable conversions
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12ISR(void) {
    __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
}

#pragma vector = TIMERA0_VECTOR
__interrupt void timerA_isr() {

    __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
}
