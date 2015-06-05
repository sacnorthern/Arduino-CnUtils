/*** CrunchyNoodles Utilities and Assorted Sundry Items for Arduino ***/
/*** Brian Witt *** bwitt@value.net *** November 2013 ***/

/*** License: this file in the public domain. ***/

#include <CnUtils.h>
#include <avr/eeprom.h>
#include <avr/boot.h>
#include <avr/io.h>

// --------------------------  Magic C++ Functions  --------------------------

/// C:\Users\brian\Documents\Arduino\libraries\CnUtils\CnUtils.cpp:16: error: too few template-parameter-lists

template<>
void print3<unsigned char>( Print& outs, const char * first, unsigned char val, const char * last )
{
    outs.print( first);
    outs.print( val, DEC );
    outs.print( last );
}

template<>
void print3<unsigned int>( Print& outs, const char * first, unsigned int val, const char * last )
{
    outs.print( first);
    outs.print( val, DEC );
    outs.print( last );
}

template<>
void print3<int>( Print& outs, const char * first, int val, const char * last )
{
    outs.print( first);
    outs.print( val, DEC );
    outs.print( last );
}

template<>
void print3<const char *>( Print& outs, const char * first, const char * val, const char * last )
{
    outs.print( first);
    outs.print( val );
    outs.print( last );
}


/* ------------------------------------------------------------------- */

//------------------------
//  Get the available ram size.
//  @see http://playground.arduino.cc/Code/AvailableMemory#.UxO0Vq5lO4o
//------------------------
size_t freeRam()
{
  extern char   __heap_start, *__brkval;        // from "malloc.c"
  auto int      tos;
  return PTR2INT( &tos ) - ((__brkval == 0) ? PTR2INT( &__heap_start ) : PTR2INT(__brkval));
}  // FREE RAM


/* ------------------------------------------------------------------- */

/***
 *   Format a fixed-width HEX value with leading zeroes.
 *   If value smaller than the field, extra 'hexValue' digits are print()-ed.
 *   Handles max-size of 2 bytes on hex value and 'width' max of 5.
 *   Calls "outs.print( uint16_t, HEX )" to display the value.
 */
void printHexWidth( Print &outs, uint16_t hexValue, uint8_t width )
{
    switch( width )
    {
        case 5 :
                if( hexValue <= 0x0FFFF ) outs.print( '0' );
        case 4 :
                if( hexValue <= 0x0FFF ) outs.print( '0' );
        case 3 :
                if( hexValue <= 0x0FF ) outs.print( '0' );
        case 2 :
                if( hexValue <= 0x0F ) outs.print( '0' );
                break;
        default :
                // handles width of 1 and 0 ...
                break;
    }
    outs.print( hexValue, HEX );
}

/* ------------------------------------------------------------------- */

/*  Code will work with 8 and 16 bytes displayed across the line. */
#define DUMP_WIDTH  8

/***
 *   Dump a section EE-memory to 'outs'.  Bytes are read using:
 *       eeprom_read_byte( eeOffset++ )
 *   until 'size' bytes have been processed.
 */
void dumpEE( Print &outs, uint16_t eeOffset, uint16_t size )
{
    char  ascii[ 16 + 1 ];
    uint8_t  j;
    uint8_t  b;

    while( size > 0 )
    {
        strcpy( ascii, "................" );

        printHexWidth( outs, eeOffset, 3 );
        outs.print( " : " );

        for( j = 0 ; j < DUMP_WIDTH && size > 0 ; ++j, --size, ++eeOffset )
        {
            b = eeprom_read_byte( (const uint8_t *) eeOffset );
            printHexWidth( outs, b, 2 );

            outs.print( ' ' );

            //  If printable, then print the ASCII representation.
            if( 32 <= b && b <= 0x7E )
                ascii[ j ] = b;
        }
        
        ascii[ j ] = 0;
        for( ; j < DUMP_WIDTH ; ++j )
            outs.print("   ");
        outs.print( " |" );
        outs.print( ascii );
        outs.println( '|' );
    }

}   /* end EeValues::dumpEE() */

#undef DUMP_WIDTH


/***
 *   Read CPU's signature bytes, store to buffer, minimum of 8 bytes.
 *   If MPU signature cannot be read, returns as 3 zero bytes.
 *   Arduino 1.5 : __AVR_ATmega328P__ does not define SIGRD.
 *
 *   @seealso http://electronics.stackexchange.com/questions/31048/can-an-atmega-or-attiny-device-signature-be-read-while-running
 *   @seealso http://electronics.stackexchange.com/questions/58386/how-can-i-detect-which-arduino-board-or-which-controller-in-software/58388#58388
 *   @return actual number of bytes stored into 'outs', <0 on error.
 */
int8_t
getCpuSignatureBytes( uint8_t * outs, uint8_t size_outs )
{

    if( size_outs < 5 )
        return (int8_t) -1;

    outs[0] = highByte( VENDOR_ID_ATMEL );
    outs[1] = lowByte( VENDOR_ID_ATMEL );

#if defined (__AVR_ATmega328P__) && !defined(SIGRD)
//  missing bit in "define SPMCSR _SFR_IO8(0x37)"
    outs[2] = 0;
    outs[3] = 0;
    outs[4] = 0;
#else
    /* this code is very Arduino specific. */
    outs[2] = boot_signature_byte_get( 0 );
    outs[3] = boot_signature_byte_get( 1 );
    outs[4] = boot_signature_byte_get( 2 );
#endif

    return( 5 );
}   /* end getCpuSignatureBytes() */

