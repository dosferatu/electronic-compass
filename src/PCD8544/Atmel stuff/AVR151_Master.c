//***************************************************************************
// A P P L I C A T I O N   N O T E   F O R   T H E   A V R   F A M I L Y
//
// Number               : AVR151
// File Name            : "avr151_Master.c"
// Title                : Setup and Use The SPI
// Date                 : 00.09.20
// Version              : 1.0
// Target MCU           : Any AVR with SPI
//
// DESCRIPTION
// This Application note shows how to enable and use the on-board SPI of the 
// AVR's in Master- and in Slave-Mode. 
//
// This file contains the code of all the examples. To switch between the examples
// you will have to enable the call of the corresponding routines.
// (see the comments in the main program at the bottom)
//
// Modified 2004-10-25 RAA
//
//**************************************************************************

#include "inavr.h"
#include "ioavr.h"

char*    TextString    = "AVR communicating via the SPI"+0x00;
char*    PtrToStrChar;                  	// Pointer to certain Character in String
char     ClearToSend   = 1;             	// String send complete bit

// Interrupt Routine Master Mode (interrupt controlled)
#pragma vector=SPI_STC_vect
__interrupt void ISR_SPI (void)
{
        PtrToStrChar++;                 	// Point to next Char in String
        if (*PtrToStrChar != 0)         	// if end not reached
        {
                SPDR  = *PtrToStrChar;  	// send Character
        }
        else ClearToSend = 1;           	// if end reached enable transmission of next String
}

// Intialization Routine Master Mode (polling)
void Init_Master (void)
{
        volatile char IOReg;
        // set PB4(/SS), PB5(MOSI), PB7(SCK) as output 
        DDRB    = (1<<PB4)|(1<<PB5)|(1<<PB7);
        // enable SPI in Master Mode with SCK = CK/4
        SPCR    = (1<<SPE)|(1<<MSTR);
        IOReg   = SPSR;                 	// clear SPIF bit in SPSR
        IOReg   = SPDR;
}

// Intialization Routine Master Mode (interrupt controlled)
void Init_Master_IntContr (void)
{
        volatile char IOReg;
        // set PB4(/SS), PB5(MOSI), PB7(SCK) as output 
        DDRB  = (1<<PB4)|(1<<PB5)|(1<<PB7);
        // enable SPI Interrupt and SPI in Master Mode with SCK = CK/16
        SPCR  = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR0);
        IOReg   = SPSR;                 	// clear SPIF bit in SPSR
        IOReg   = SPDR;
        __enable_interrupt();
}



// Sending Routine Master Mode (polling)
void Master_Send (void)
{
        PtrToStrChar  = TextString;             // Set Pointer to beginning of String
        while   (*PtrToStrChar != 0)            // if not end of String
        {
                SPDR  = *PtrToStrChar;          // send Character
                while (!(SPSR & (1<<SPIF)));    // wait until Char is sent 
                PtrToStrChar++;                 // Point to next char in String
        }
}


// Sending Routine Master Mode (interrupt controlled)
void Master_Send_IntContr (void)
{
        if (ClearToSend == 1){                  // if no transmission is in progress
                PtrToStrChar  = TextString;     // Set Pointer to beginning of String
                                                // initiate new transmission by 
                SPDR = *PtrToStrChar;           // sending first Char of new String
                ClearToSend = 0;                // block initiation of new transmissions
        }
}

void main (void)
{
        char KeyPressed = 0x00;
        DDRD  = 0xFF;
        PORTD = 0x00;
        // enable next line for Example 1
        Init_Master ();                         // Initialization (polling)
        // enable next line for Example 2
        // Init_Master_IntContr();              // Initialization (interrupt controlled)
        while (1){
                if (PINA != 0xFF){
                        if (KeyPressed == 0x00){
                                KeyPressed = 0x01;
                                PORTD = ~PORTD; // toggles Port D 
                                // enable next line for Example 1
                                Master_Send ();
                                // enable next line for Example 2
                                // Master_Send_IntContr();
                        }
                }       
                else KeyPressed = 0x00;
        }
}

