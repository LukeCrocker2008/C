/*--------------------------------------------------------
* File: fp.c
* Description: A Model & Simulation of Object inside MSP430 Experimenter’s Board
* Input: Signals from Joystick to move the object
* Output: Response from different peripherals depending on object's position
* Author: Luke Crocker
* Lab Section: 01
* Date: 4/23/19
*--------------------------------------------------------*/

#include "Board.h" // LCD
#include "LCD.h"
#include "peripherals.h"
#include "joystick.h"
#include "map.h" // Model and Simulation

#define DEFAULT_HOR 23 // (WIDTH/2)
#define DEFAULT_VER 31 // (LENGTH/2)

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // stop watchdog timer
    FLL_CTL0 |= DCOPLUS + XCAP18PF;     // DCO+ set, freq = xtal x D x N+1
    SCFI0 |= FN_4 + FLLD_2;             // DCO range control
    SCFQCTL = 30;                       // (30+1) x 32768 x 2 = 2.03 MHz

    i = DEFAULT_HOR;                    // Horizontal position of object
    j = DEFAULT_VER;                    // Vertical position of object
    TimerA_setup();                     // Setup timer to send ADC data
    ADC_setup();                        // Setup ADC
    initLCD_A();                        // Initialize LCD_A
    initLEDs();                         // Initialize LEDs
    SPI_setup();                        // LED3

    _EINT();                            // Enable Interrupts

    while (1)
    {
        ADC12CTL0 |= ADC12SC;               // Start conversions
        if(SW1 == 0)                        // Reset object to Default Position
        {
            i = DEFAULT_HOR;                // Horizonal Axis
            j = DEFAULT_VER;                // Vertical Axis
        }
        watchJs();                          // Check samples from Joystick for object movement
        objPosition();                      // Check object position in proximity to the peripherals
        __bis_SR_register(LPM0_bits + GIE); // Enter LPM0
    }
}

