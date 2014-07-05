#!/bin/sh
#

VER=1.16
curl -v -# -T /home/kraus/src/u8g/u8glib/tools/release/arm/u8glib_arm_v${VER}.zip -uolikraus:xyz -H "X-Bintray-Package:ARM" -H "X-Bintray-Version:${VER}" https://api.bintray.com/content/olikraus/u8glib/
curl -v -# -T /home/kraus/src/u8g/u8glib/tools/release/arduino/u8glib_arduino_v${VER}.zip -uolikraus:xyz -H "X-Bintray-Package:Arduino" -H "X-Bintray-Version:${VER}" https://api.bintray.com/content/olikraus/u8glib/
curl -v -# -T /home/kraus/src/u8g/u8glib/tools/release/avr/u8glib_avr_v${VER}.zip -uolikraus:xyz -H "X-Bintray-Package:AVR" -H "X-Bintray-Version:${VER}" https://api.bintray.com/content/olikraus/u8glib/
