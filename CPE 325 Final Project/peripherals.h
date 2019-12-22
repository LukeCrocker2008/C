#include <msp430.h>
#include <msp430xG46x.h>
#include <stdio.h>

#define SW1 (P1IN&BIT0)
#define SW2 (P1IN&BIT1)

void lcd() //LCD
{
        testChar();
        testSpecialChar();
        testSigLvl();
        testBatt();
        testPwrLvl();
        testFunc();
        testArrow();
        testSymbol();
        testAll();
}

void SPI_setup(void) //LED3
{
    UCB0CTL0 = UCMSB + UCMST + UCSYNC;// Sync. mode, 3-pin SPI, Master mode, 8-bit data
    UCB0CTL1 = UCSSEL_2 + UCSWRST; // SMCLK and Software reset
    UCB0BR0 = 0x02;                // Data rate = SMCLK/2 ~= 500kHz
    UCB0BR1 = 0x00;
    P3SEL |= BIT1 + BIT2 + BIT3;   // P3.1,P3.2,P3.3 option select
    UCB0CTL1 &= ~UCSWRST;          // **Initialize USCI state machine**
}

void SPI_setState(unsigned char State) //LED3
{
    while(P3IN & 0x01);           // Verifies busy flag
    IFG2 &= ~UCB0RXIFG;
    UCB0TXBUF = State;            // Write new state
    while (!(IFG2 & UCB0RXIFG));  // USCI_B0 TX buffer ready?
}

unsigned char SPI_getState(void)
{
    while((P3IN & 0x01));          // Verifies busy flag
    IFG2 &= ~UCB0RXIFG;
    UCB0TXBUF = 0x00;     // Dummy write to start SPI
    while (!(IFG2 & UCB0RXIFG));   // USCI_B0 TX buffer ready?
    return UCB0RXBUF;
}

// LEDs
void initLEDs()
{
    P2DIR |= BIT2+BIT1;
    P2OUT &= ~BIT2;             // LED1 is OFF
    P2OUT &= ~BIT1;             // LED2 is OFF

    P5DIR |= BIT1;
    P5OUT &= ~BIT1;             // LED4 is OFF

    P4DIR |= BIT6;
    P4OUT &= ~BIT6;             // LED6 is OFF

    P10DIR |= BIT6;
    P10OUT &= ~BIT6;             // LED5 is OFF
}

void toggleLED1andLED2(unsigned int position)
{
    unsigned int k;
    for(k = 0; k < (position*2); k++);
    P2OUT ^= BIT2+BIT1;
//    TB0CTL = TBSSEL_2 + MC_1;  // SMCLK is clock source, UP mode
//    TB0CCTL1 = OUTMOD_4;       // TB0 output is in toggle mode
//    TB0CCTL0 = OUTMOD_4;       // TB0 output is in toggle mode
//    TB0CCR0 = position;
//    P2DIR |= BIT2+BIT1;
//    P2SEL |= BIT2+BIT1;
}
void toggleLED3(int position)
{
    if(SPI_getState() != position)
        SPI_setState(position);
}

void toggleLED4(unsigned int position)
{
    unsigned int k;
    for(k = 0; k < position; k++);
    P5OUT ^= BIT1;
}

void toggleLED5(unsigned int position)
{
    // H9 Pin 5 -> P10.6
    unsigned int k;
    for(k = 0; k < (position*2); k++);
    P10OUT ^= BIT6;
}

void toggleLED6(unsigned int position)
{
    // H3 Pin 7 -> P4.6
    unsigned int k;
    for(k = 0; k < position; k++);
    P4OUT ^= BIT6;
}

// Buzzer

void OoB_Buzzer()
{
    TB0CCTL4 = OUTMOD_4;       // TB0 output is in toggle mode
    TB0CTL = TBSSEL_2 + MC_1;  // SMCLK is clock source, UP mode
    TB0CCR0 = 2030;
    P3DIR |= BIT5;             // P3 Bit 5 set to output
    P3SEL |= BIT5;             // P3 BIT 5 set to TB4
}

void SW2_Buzzer(int position)
{
    TB0CCTL4 = OUTMOD_4;       // TB0 output is in toggle mode
    TB0CTL = TBSSEL_2 + MC_1;  // SMCLK is clock source, UP mode
    TB0CCR0 = position;
    P3DIR |= BIT5;             // P3 Bit 5 set to output
    P3SEL |= BIT5;             // P3 BIT 5 set to TB4
}

