/**
 * @file    fontutf8.ino
 * @brief   font api test for u8g lib
 * @author  Yunhui Fu (yhfudev@gmail.com)
 * @version 1.0
 * @date    2015-04-19
 * @copyright GPL/BSD
 */
#if defined(ARDUINO)
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <U8glib.h>
#else
#include <unistd.h>
#define delay(a) usleep(a)
#endif

