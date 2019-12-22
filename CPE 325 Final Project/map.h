
// Map

#define LENGTH 63 // Horizontal
#define WIDTH  47 // Vertical

//int BOARD_MAP[WIDTH][LENGTH]; // Software Model of Board

// LED1 & LED2

// 1st Layer

#define LED1andLED2_ilb_f 6  // i lower bound
#define LED1andLED2_jlb_f 37 // j lower bound
#define LED1andLED2_iub_f 12 // i upper bound
#define LED1andLED2_jub_f 43 // j upper bound

// 2nd Layer

#define LED1andLED2_ilb_s 0  // i lower bound
#define LED1andLED2_jlb_s 32 // j lower bound
#define LED1andLED2_iub_s 18 // i upper bound
#define LED1andLED2_jub_s 44 // j upper bound

// LED3

// 1st Layer

#define LED3_ilb_f 0  // i lower bound
#define LED3_jlb_f 48 // j lower bound
#define LED3_iub_f 12 // i upper bound
#define LED3_jub_f 56 // j upper bound

// 2nd Layer

#define LED3_ilb_s 0  // i lower bound
#define LED3_jlb_s 46 // j lower bound
#define LED3_iub_s 18 // i upper bound
#define LED3_jub_s 59 // j upper bound

// 3rd Layer

#define LED3_ilb_t 0  // i lower bound
#define LED3_jlb_t 44 // j lower bound
#define LED3_iub_t 25 // i upper bound
#define LED3_jub_t 63 // j upper bound

// LED4

// 1st Layer

#define LED4_ilb_f 19  // i lower bound
#define LED4_jlb_f 17   // j lower bound
#define LED4_iub_f 30  // i upper bound
#define LED4_jub_f 26  // j upper bound

// 2nd Layer

#define LED4_ilb_s 12  // i lower bound
#define LED4_jlb_s 16   // j lower bound
#define LED4_iub_s 33  // i upper bound
#define LED4_jub_s 30  // j upper bound

// LED5

// 1st Layer

#define LED5_ilb_f 26 // i lower bound
#define LED5_jlb_f 30 // j lower bound
#define LED5_iub_f 40 // i upper bound
#define LED5_jub_f 43 // j upper bound

// 2nd Layer

#define LED5_ilb_s 20 // i lower bound
#define LED5_jlb_s 24 // j lower bound
#define LED5_iub_s 46 // i upper bound
#define LED5_jub_s 50 // j upper bound

// LED6

// 1st Layer

#define LED6_ilb_f 0 // i lower bound
#define LED6_jlb_f 8 // j lower bound
#define LED6_iub_f 7 // i upper bound
#define LED6_jub_f 24 // j upper bound

// 2nd Layer

#define LED6_ilb_s 0 // i lower bound
#define LED6_jlb_s 0 // j lower bound
#define LED6_iub_s 10 // i upper bound
#define LED6_jub_s 34 // j upper bound

// LCD

// 1st Layer

#define LCD_ilb_f 12 // i lower bound
#define LCD_jlb_f 2 // j lower bound
#define LCD_iub_f 33 // i upper bound
#define LCD_jub_f 15 // j upper bound

// SW2

// 1st Layer

#define SW2_ilb_f 29 // i lower bound
#define SW2_jlb_f 56 // j lower bound
#define SW2_iub_f 42 // i upper bound
#define SW2_jub_f 63 // j upper bound

#define SW2_ilb_s 24 // i lower bound
#define SW2_jlb_s 50 // j lower bound
#define SW2_iub_s 47 // i upper bound
#define SW2_jub_s 63 // j upper bound

#define SW2_ilb_t 13 // i lower bound
#define SW2_jlb_t 44 // j lower bound
#define SW2_iub_t 47 // i upper bound
#define SW2_jub_t 63 // j upper bound

int i; // Horizontal position of object
int j; // Vertical position of object

// Functions

void watchJs() //Move object
{
    if (Xper >= 90 && Xper <= 100 && Yper >= 90 && Yper <= 100) // Move top-left
    {
        i--;
        j--;
        if(i < 0)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            i = 0;
        }
        if (j < 0)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            j = 0;
        }
//        printf("Top-left: i = %i | j = %i \n", i, j);
    }

    if (Xper >= 90 && Xper <= 100 && Yper >= 0 && Yper <= 10) // Move bottom-left
    {
        i--;
        j++;
        if(i < 0)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            i = 0;
        }
        if (j > LENGTH)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            j = LENGTH;
        }
//       printf("Bottom-left: i = %i | j = %i \n", i, j);
    }

    if (Xper >= 95 && Xper <= 100 && Yper >= 43 && Yper <= 53) // Move left
    {
        i--;
        if(i < 0)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            i = 0;
        }
//        printf("Left: i = %i | j = %i \n", i, j);
    }

    if (Xper >= 45 && Xper <= 55 && Yper >= 95 && Yper <= 100) // Move up
    {
        j--;
        if(j < 0)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            j = 0;
        }
//        printf("Up: i = %i | j = %i \n", i, j);
    }

    if (Xper >= 45 && Xper <= 55 && Yper >= 0 && Yper <= 10) // Move down
    {
        j++;
        if(j > LENGTH)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            j = LENGTH;
        }
//        printf("Down: i = %i | j = %i \n", i, j);
    }

    if (Xper >= 0 && Xper <= 10 && Yper >= 43 && Yper <= 53) // Move right
    {
        i++;
        if(i > WIDTH)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            i = WIDTH;
        }
//        printf("Right: i = %i | j = %i \n", i, j);
    }

    if (Xper >= 0 && Xper <= 10 && Yper >= 0 && Yper <= 10) // Move bottom-right
    {
        i++;
        j++;
        if(i > WIDTH)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            i = WIDTH;
        }
        if (j > LENGTH)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            j = LENGTH;
        }
//        printf("Bottom-right: i = %i | j = %i \n", i, j);
    }

    if (Xper >= 0 && Xper <= 10 && Yper >= 90 && Yper <= 100) // Move top-right
    {
        i++;
        j--;
        if(i > WIDTH)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            i = WIDTH;
        }
        if (j < 0)
        {
            OoB_Buzzer(); // Buzzer for out of bounds
            j = 0;
        }
//        printf("Top-right: i = %i | j = %i \n", i, j);
    }
}

void objPosition()
{

    if( i >= LED1andLED2_ilb_f && i <= LED1andLED2_iub_f && j >= LED1andLED2_jlb_f && j <= LED1andLED2_jub_f ) // LED1 & LED2
    {
        toggleLED1andLED2(50);
    } else if ( i >= LED1andLED2_ilb_s && i <= LED1andLED2_iub_s && j >= LED1andLED2_jlb_s && j <= LED1andLED2_jub_s )
    {
        toggleLED1andLED2(5000);
    } else
    {
        P2OUT &= ~BIT2;
        P2OUT &= ~BIT1;
//        P2DIR &= ~(BIT2+BIT1);
//        P2SEL &= ~(BIT2+BIT1);
    }

    if(i >= LED3_ilb_f && i <= LED3_iub_f && j >= LED3_jlb_f && j <= LED3_jub_f) // LED3
    {
        toggleLED3(1);
    } else if (i >= LED3_ilb_s && i <= LED3_iub_s && j >= LED3_jlb_s && j <= LED3_jub_s)
    {
        toggleLED3(3);
    } else if (i >= LED3_ilb_t && i <= LED3_iub_t && j >= LED3_jlb_t && j <= LED3_jub_t)
    {
        toggleLED3(31);
    }
    else
    {
        toggleLED3(0);              // LED3 is OFF
    }

    if(i >= LED4_ilb_f && i <= LED4_iub_f && j >= LED4_jlb_f && j <= LED4_jub_f) // LED4
    {
        toggleLED4(50);
    } else if (i >= LED4_ilb_s && i <= LED4_iub_s && j >= LED4_jlb_s && j <= LED4_jub_s)
    {
        toggleLED4(5000);
    }  else
    {
        P5OUT &= ~BIT1;             // LED4 is OFF
    }

    if(i >= LED5_ilb_f && i <= LED5_iub_f && j >= LED5_jlb_f && j <= LED5_jub_f) // LED5
    {
        toggleLED5(50);
    } else if(i >= LED5_ilb_s && i <= LED5_iub_s && j >= LED5_jlb_s && j <= LED5_jub_s) // LED5
    {
        toggleLED5(5000);
    } else
    {
        P10OUT &= ~BIT6;             // LED5 is OFF
    }

    if(i >= LED6_ilb_f && i <= LED6_iub_f && j >= LED6_jlb_f && j <= LED6_jub_f) // LED6
    {
        toggleLED6(50);
    } else if(i >= LED6_ilb_s && i <= LED6_iub_s && j >= LED6_jlb_s && j <= LED6_jub_s) // LED6
    {
        toggleLED6(5000);
    }  else
    {
        P4OUT &= ~BIT6;             // LED6 is OFF
    }

    if(i >= LCD_ilb_f && i <= LCD_iub_f && j >= LCD_jlb_f && j <= LCD_jub_f) // LED4
    {
        lcd();
    }

    if(i >= SW2_ilb_f && i <= SW2_iub_f && j >= SW2_jlb_f && j <= SW2_jub_f && SW2 == 0) // LED6
    {
        SW2_Buzzer(3223);
    } else if (i >= SW2_ilb_s && i <= SW2_iub_s && j >= SW2_jlb_s && j <= SW2_jub_s && SW2 == 0)
    {
        SW2_Buzzer(5148);
    } else if (i >= SW2_ilb_t && i <= SW2_iub_t && j >= SW2_jlb_t && j <= SW2_jub_t && SW2 == 0)
    {
        SW2_Buzzer(8125);
    }
    else
    {
        P3DIR &= ~BIT5;             // P3 Bit 5 set to output
        P3SEL &= ~BIT5;             // P3 BIT 5 set to TB4
    }
}

