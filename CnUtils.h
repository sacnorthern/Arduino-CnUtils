/*** CrunchyNoodles Utilities and Assorted Sundry Items for Arduino ***/
/*** Brian Witt *** bwitt@value.net *** November 2013 ***/

/*** License: this file in the public domain. ***/

#ifndef _CRUNCHYNOODLES_UTILS_H
#define _CRUNCHYNOODLES_UTILS_H

#include <Arduino.h>


// --------------------------  Magical Definitions  --------------------------

/***  Return number of elements in an array.  */
#define NELEMENTS(_ary)    (sizeof(_ary) / sizeof(_ary[0]))

/*** Convert a pointer into an integeral type. */
#define PTR2INT(_p)    ( (char *)(_p) - (char *)0 )


//  A few boards don't have 'LED_BUILTIN', use Firmata as second-best source.
#if defined (__AVR_ATmega32U4__)
  //  32U4 of Leonardo and BBLeo need assist.
  #define  LED_BUILTIN    VERSION_BLINK_PIN
#endif


/*** A C#-like Key and Value pairing. */
template <class TKey, class TValue> struct KeyValuePair
{
    TKey  key;
    TValue value;
};


// --------------------------  Magic C++ Functions  --------------------------

/***
 *   Allow Print-things, e.g. HardwareSerial, to print a prefix string, a number,
 *   and a suffix-string.
 *
 *   I would love if C++ had extension classes like C#.  I looked at IO stream
 *   overloads but could not get it to work.  I want to see this:
 *      Serial.print3( "open==", 5, "==close" );
 *
 */
template< typename MiddleType >
void print3( Print& p, const char * first, MiddleType val, const char * last );


// ---------------------------  Helpers Functions  ---------------------------

/***
 *   A small-value version of map() using 'uint8_t' instead of 'long' data types.
 */
static inline uint8_t map( uint8_t value, uint8_t fromLow, uint8_t fromHigh, uint8_t toLow, uint8_t toHigh )
{
    return ((uint16_t)value - fromLow) * ((uint16_t)toHigh - toLow) / ((uint16_t)fromHigh - fromLow) + toLow;
}

//-----------------------
//  Get the available ram size, i.e. memory not yet claimed by malloc().
//  This is measurement of current "top of heap".  If there are holes inside
//  the heap, then more than freeRam() can be allocated.
//-----------------------
extern size_t     freeRam();

extern void       printHexWidth( Print &outs, uint16_t hexValue, uint8_t width );

extern void       dumpEE( Print &outs, uint16_t eeOffset, uint16_t size );

/*** Read CPU's signature bytes, store to buffer, returns actual stored count as return value */
extern int8_t     getCpuSignatureBytes( uint8_t * outs, uint8_t size_outs );
#define VENDOR_ID_ATMEL   0x1114
#define VENDOR_ID_FREESCALE   _needs_a_value_

#endif
