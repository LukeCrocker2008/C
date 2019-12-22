/*--------------------------------------------------------
* File: slave.c
* Description: This program is a slave to the SPI.c program.
* Input: integer
* Output: integer
* Author: Luke Crocker
* Lab Section: 01
* Date: 3/13/19
*--------------------------------------------------------*/

#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_STATE   0x00      // Character NULL - used for dummy write operation

#define LED_ON          0x01
#define LED_OFF         0x00

#define SET_BUSY_FLAG()   P1OUT |= 0x10
#define RESET_BUSY_FLAG() P1OUT &= ~0x10

#define SET_LED()       P1OUT |= 0x01
#define RESET_LED()     P1OUT &= ~0x01

unsigned char LEDState;
unsigned char NextState;

int divider = 1;
int wdflag = 1;

void SPI_setup(void) {
    USICTL0 |= USISWRST;          // Set UCSWRST -- needed for re-configuration process
    USICTL0 |= USIPE5 + USIPE6 + USIPE7 + USIOE; // SCLK-SDO-SDI port enable,MSB first
    USICTL1 = USIIE;              // USI  Counter Interrupt enable
    USICTL0 &= ~USISWRST;         // **Initialize USCI state machine**
}

void SPI_initComm(void) {
    USICNT = 8;                   // Load bit counter, clears IFG
    USISRL = LEDState;            // Set LED state
    RESET_BUSY_FLAG();            // Reset busy flag
}

void main(void)
{
    WDTCTL = WDT_MDLY_32;     // 32ms interval

    P1DIR |= BIT0;                // P1.0 as output - LED3
    P1DIR |= BIT4;                // P1.4 as output - Busy flag

    BCSCTL1 = CALBC1_1MHZ;        // Set DCO
    DCOCTL = CALDCO_1MHZ;



    LEDState = LED_OFF;
    SPI_setup();                  // Setup USI module in SPI mode
    SPI_initComm();               // Initialization communication

    IE1 |= WDTIE;                     // Enable WDT interrupt

    while(1)
    {

        switch (NextState)
        {
            case 0:            // Dummy operation; no change in the state
                LEDState = LED_OFF;
                wdflag = 0;
                RESET_BUSY_FLAG();        // Clears busy flag - ready for new communication
                break;
//            case  255:
//                USISRL = divider;       // Prepares reply to master with new state
//                wdflag = 0;
//                RESET_BUSY_FLAG();        // Clears busy flag - ready for new communication
//                break;
            default  :
                LEDState = NextState;   // New state
                wdflag = 1;
                RESET_BUSY_FLAG();        // Clears busy flag - ready for new communication
                break;
        }


     // Change the status of LED depending on the command
     if (LEDState == LED_OFF)
     {
         RESET_LED();
     }
     else
     {
         SET_LED();
         USISRL = divider;       // Prepares reply to master with new state
         RESET_BUSY_FLAG();        // Clears busy flag - ready for new communication
     }

      _BIS_SR(LPM0_bits+GIE);        // Enter Low Power Mode 0
     }
}

#pragma vector = USI_VECTOR
__interrupt void USI_ISR(void)
{
    SET_BUSY_FLAG();              // Set busy flag - busy with new communication

    if(USISRL <= 99 || USISRL == 255)
        NextState = USISRL;           // Read new command
    if(NextState <= 99)
        divider = NextState;
    USICNT = 8;                   // Load bit counter for next TX
    _BIC_SR_IRQ(LPM0_bits);       // Exit from LPM0 on RETI
}

#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    static int count = 1; // Counter for LED3 to blink at 31.2 Hz/divider
    if(wdflag == 1)
    {
        if(count >= divider)
        {
            P1OUT ^= 0x01;
            count = 1;
        }
        else
        {
            count++;
        }
    }
}



