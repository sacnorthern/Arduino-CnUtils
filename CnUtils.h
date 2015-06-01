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


// ---------------------------  Helpers Functions  ---------------------------

/***
 *   A small-value version of map() using 'uint8_t' instead of 'long' data types.
 */
static inline uint8_t map( uint8_t value, uint8_t fromLow, uint8_t fromHigh, uint8_t toLow, uint8_t toHigh )
{
    return ((uint16_t)value - fromLow) * ((uint16_t)toHigh - toLow) / ((uint16_t)fromHigh - fromLow) + toLow;
}

//-----------------------
//  Get the available ram
//-----------------------
extern size_t     freeRam();

extern void       printHexWidth( Print &outs, uint16_t hexValue, uint8_t width );

extern void       dumpEE( Print &outs, uint16_t offset, uint16_t size );

#endif
