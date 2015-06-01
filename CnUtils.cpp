/*** CrunchyNoodles Utilities and Assorted Sundry Items for Arduino ***/
/*** Brian Witt *** bwitt@value.net *** November 2013 ***/

/*** License: this file in the public domain. ***/

#include <CnUtils.h>
#include <avr/eeprom.h>


/* ------------------------------------------------------------------- */

//------------------------
//  Get the available ram
//------------------------
size_t freeRam()
{
  // Defined in "malloc.c".
  extern char   __heap_start, *__brkval;        // from "malloc.c"
  auto int      tos;
  return PTR2INT( &tos ) - (__brkval == 0 ? PTR2INT( &__heap_start ) : PTR2INT(__brkval));
}  // FREE RAM


/* ------------------------------------------------------------------- */

/***
 *   Format a fixed-width HEX value with leading zeroes.
 *   Handles max-size of 2 bytes on hex value and 'width' max of 5.
 *   Calls "outs.print( uint16_t, HEX )" to display the value.
 *   If value larger than the field, extra 'hexValue' digits are print()-ed.
 */
void printHexWidth( Print &outs, uint16_t hexValue, uint8_t width )
{
    switch( width )
    {
        case 5 :
                if( hexValue <= 9999 ) outs.print( '0' );
        case 4 :
                if( hexValue <= 999 ) outs.print( '0' );
        case 3 :
                if( hexValue <= 99 ) outs.print( '0' );
        case 2 :
                if( hexValue <= 9 ) outs.print( '0' );
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
 *   Dump a section EE-memory to 'outs'.  Bytes are read using
 *       eeprom_read_byte( offset++ )
 *   until 'size' bytes have been processed.
 */
void dumpEE( Print &outs, uint16_t offset, uint16_t size )
{
    char  ascii[ 16 + 1 ];
    uint8_t  j;
    uint8_t  b;

    while( size > 0 )
    {
        strcpy( ascii, "................" );

        printHexWidth( outs, offset, 3 );
        outs.print( " : " );

        for( j = 0 ; j < DUMP_WIDTH && size > 0 ; ++j, --size, ++offset )
        {
            b = eeprom_read_byte( (const uint8_t *) offset );
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

