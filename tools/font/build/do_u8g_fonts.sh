#!/bin/bash


echo u8glib_4
../bdf2u8g/bdf2u8g -f 1 ../bdf/u8glib_4.bdf u8g_font_u8glib_4 u8g_font_u8glib_4.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/u8glib_4.bdf u8g_font_u8glib_4r u8g_font_u8glib_4r.c > /dev/null

echo m2icon
../bdf2u8g/bdf2u8g -f 1 -b 65 -e 104 ../bdf/m2icon_5.bdf u8g_font_m2icon_5 u8g_font_m2icon_5.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 65 -e 104  ../bdf/m2icon_7.bdf u8g_font_m2icon_7 u8g_font_m2icon_7.c > /dev/null
../bdf2u8g/bdf2u8g  -b 65 -e 105  ../bdf/m2icon_9.bdf u8g_font_m2icon_9 u8g_font_m2icon_9.c > /dev/null

echo cursor
../bdf2u8g/bdf2u8g -s 32 ../bdf/cursor.bdf u8g_font_cursor u8g_font_cursor.c > /dev/null
../bdf2u8g/bdf2u8g -e 80 -s 32 ../bdf/cursorr.bdf u8g_font_cursorr u8g_font_cursorr.c > /dev/null
echo cu12
../bdf2u8g/bdf2u8g ../bdf/cu12.bdf u8g_font_cu12 u8g_font_cu12.c  > /dev/null
../bdf2u8g/bdf2u8g -l 67 -u 75 ../bdf/cu12.bdf u8g_font_cu12_67_75 u8g_font_cu12_67_75.c  > /dev/null
../bdf2u8g/bdf2u8g -l 75 -b 32 -e 79 ../bdf/cu12.bdf u8g_font_cu12_75r u8g_font_cu12_75r.c  > /dev/null
#../bdf2u8g/bdf2u8g -l 78 -u 79 ../bdf/cu12.bdf u8g_font_cu12_78_79 u8g_font_cu12_78_79.c
echo micro
../bdf2u8g/bdf2u8g -f 1 ../bdf/micro.bdf u8g_font_micro u8g_font_micro.c  > /dev/null
#../bdf2u8g/bdf2u8g -f 1 ../bdf/micro.bdf u8g_font_micror u8g_font_micror.c  > /dev/null
echo "4x6"
../bdf2u8g/bdf2u8g -f 1 ../bdf/4x6.bdf u8g_font_4x6 u8g_font_4x6.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/4x6.bdf u8g_font_4x6r u8g_font_4x6r.c  > /dev/null
#../bdf2u8g/bdf2u8g -f 1 -b 42 -e 58 ../bdf/4x6.bdf u8g_font_4x6n u8g_font_4x6n.c  > /dev/null
echo "5x7"
../bdf2u8g/bdf2u8g -f 1 ../bdf/5x7.bdf u8g_font_5x7 u8g_font_5x7.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/5x7.bdf u8g_font_5x7r u8g_font_5x7r.c  > /dev/null
echo "5x8"
../bdf2u8g/bdf2u8g -f 1 ../bdf/5x8.bdf u8g_font_5x8 u8g_font_5x8.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/5x8.bdf u8g_font_5x8r u8g_font_5x8r.c  > /dev/null
echo "6x10"
../bdf2u8g/bdf2u8g -f 1 ../bdf/6x10.bdf u8g_font_6x10 u8g_font_6x10.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/6x10.bdf u8g_font_6x10r u8g_font_6x10r.c  > /dev/null
echo "6x12"
../bdf2u8g/bdf2u8g -f 1 ../bdf/6x12.bdf u8g_font_6x12 u8g_font_6x12.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/6x12.bdf u8g_font_6x12r u8g_font_6x12r.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 67 -u 75 -b 0 -e 255 ../bdf/6x12.bdf u8g_font_6x12_67_75 u8g_font_6x12_67_75.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 75 -b 32 -e 79 ../bdf/6x12.bdf u8g_font_6x12_75r u8g_font_6x12_75r.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 78 -u 79 -b 0 -e 255 ../bdf/6x12.bdf u8g_font_6x12_78_79 u8g_font_6x12_78_79.c  > /dev/null
echo "6x13"
../bdf2u8g/bdf2u8g -f 1 ../bdf/6x13.bdf u8g_font_6x13 u8g_font_6x13.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/6x13.bdf u8g_font_6x13r u8g_font_6x13r.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 67 -u 75 ../bdf/6x13.bdf u8g_font_6x13_67_75 u8g_font_6x13_67_75.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 75 -b 32 -e 79 ../bdf/6x13.bdf u8g_font_6x13_75r u8g_font_6x13_75r.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 78 -u 79 ../bdf/6x13.bdf u8g_font_6x13_78_79 u8g_font_6x13_78_79.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 ../bdf/6x13B.bdf u8g_font_6x13B u8g_font_6x13B.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/6x13B.bdf u8g_font_6x13Br u8g_font_6x13Br.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 ../bdf/6x13O.bdf u8g_font_6x13O u8g_font_6x13O.c  > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/6x13O.bdf u8g_font_6x13Or u8g_font_6x13Or.c  > /dev/null
echo "7x13"
../bdf2u8g/bdf2u8g -f 1 ../bdf/7x13.bdf u8g_font_7x13 u8g_font_7x13.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/7x13.bdf u8g_font_7x13r u8g_font_7x13r.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 67 -u 75 ../bdf/7x13.bdf u8g_font_7x13_67_75 u8g_font_7x13_67_75.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 75 -b 32 -e 79 ../bdf/7x13.bdf u8g_font_7x13_75r u8g_font_7x13_75r.c > /dev/null
#../bdf2u8g/bdf2u8g -l 78 -u 79 ../bdf/7x13.bdf u8g_font_7x13_78_79 u8g_font_7x13_78_79.c
../bdf2u8g/bdf2u8g -f 1 ../bdf/7x13B.bdf u8g_font_7x13B u8g_font_7x13B.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/7x13B.bdf u8g_font_7x13Br u8g_font_7x13Br.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 ../bdf/7x13O.bdf u8g_font_7x13O u8g_font_7x13O.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/7x13O.bdf u8g_font_7x13Or u8g_font_7x13Or.c > /dev/null
echo "7x14"
../bdf2u8g/bdf2u8g -f 1 ../bdf/7x14.bdf u8g_font_7x14 u8g_font_7x14.c > /dev/null
../bdf2u8g/bdf2u8g -f 1  -b 32 -e 127 ../bdf/7x14.bdf u8g_font_7x14r u8g_font_7x14r.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 ../bdf/7x14B.bdf u8g_font_7x14B u8g_font_7x14B.c > /dev/null
../bdf2u8g/bdf2u8g -f 1  -b 32 -e 127 ../bdf/7x14B.bdf u8g_font_7x14Br u8g_font_7x14Br.c > /dev/null
echo "8x13"
../bdf2u8g/bdf2u8g -f 1 ../bdf/8x13.bdf u8g_font_8x13 u8g_font_8x13.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/8x13.bdf u8g_font_8x13r u8g_font_8x13r.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 67 -u 75 ../bdf/8x13.bdf u8g_font_8x13_67_75 u8g_font_8x13_67_75.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -l 75 -b 32 -e 79 ../bdf/8x13.bdf u8g_font_8x13_75r u8g_font_8x13_75r.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 ../bdf/8x13B.bdf u8g_font_8x13B u8g_font_8x13B.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/8x13B.bdf u8g_font_8x13Br u8g_font_8x13Br.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 ../bdf/8x13O.bdf u8g_font_8x13O u8g_font_8x13O.c > /dev/null
../bdf2u8g/bdf2u8g -f 1 -b 32 -e 127 ../bdf/8x13O.bdf u8g_font_8x13Or u8g_font_8x13Or.c > /dev/null
echo "9x15"
../bdf2u8g/bdf2u8g ../bdf/9x15.bdf u8g_font_9x15 u8g_font_9x15.c > /dev/null
../bdf2u8g/bdf2u8g -b 32 -e 127 ../bdf/9x15.bdf u8g_font_9x15r u8g_font_9x15r.c > /dev/null
../bdf2u8g/bdf2u8g -l 67 -u 75 ../bdf/9x15.bdf u8g_font_9x15_67_75 u8g_font_9x15_67_75.c > /dev/null
../bdf2u8g/bdf2u8g -l 75 -b 32 -e 79 ../bdf/9x15.bdf u8g_font_9x15_75r u8g_font_9x15_75r.c > /dev/null
../bdf2u8g/bdf2u8g -l 78 -u 79 ../bdf/9x15.bdf u8g_font_9x15_78_79 u8g_font_9x15_78_79.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/9x15B.bdf u8g_font_9x15B u8g_font_9x15B.c > /dev/null
../bdf2u8g/bdf2u8g -b 32 -e 127 ../bdf/9x15B.bdf u8g_font_9x15Br u8g_font_9x15Br.c > /dev/null
echo "9x18"
../bdf2u8g/bdf2u8g ../bdf/9x18.bdf u8g_font_9x18 u8g_font_9x18.c > /dev/null
../bdf2u8g/bdf2u8g -b 32 -e 127 ../bdf/9x18.bdf u8g_font_9x18r u8g_font_9x18r.c > /dev/null
../bdf2u8g/bdf2u8g -l 67 -u 75 ../bdf/9x18.bdf u8g_font_9x18_67_75 u8g_font_9x18_67_75.c > /dev/null
../bdf2u8g/bdf2u8g -l 75 -b 32 -e 79  ../bdf/9x18.bdf u8g_font_9x18_75r u8g_font_9x18_75r.c > /dev/null
../bdf2u8g/bdf2u8g -l 78 -u 79 ../bdf/9x18.bdf u8g_font_9x18_78_79 u8g_font_9x18_78_79.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/9x18B.bdf u8g_font_9x18B u8g_font_9x18B.c > /dev/null
../bdf2u8g/bdf2u8g -b 32 -e 127 ../bdf/9x18B.bdf u8g_font_9x18Br u8g_font_9x18Br.c > /dev/null
echo "10x20"
../bdf2u8g/bdf2u8g ../bdf/10x20.bdf u8g_font_10x20 u8g_font_10x20.c > /dev/null
../bdf2u8g/bdf2u8g -b 32 -e 127 ../bdf/10x20.bdf u8g_font_10x20r u8g_font_10x20r.c > /dev/null
../bdf2u8g/bdf2u8g -l 67 -u 75 ../bdf/10x20.bdf u8g_font_10x20_67_75 u8g_font_10x20_67_75.c > /dev/null
../bdf2u8g/bdf2u8g -l 75  -b 32 -e 79 ../bdf/10x20.bdf u8g_font_10x20_75r u8g_font_10x20_75r.c > /dev/null
../bdf2u8g/bdf2u8g -l 78 -u 79 ../bdf/10x20.bdf u8g_font_10x20_78_79 u8g_font_10x20_78_79.c > /dev/null

echo "unifont"
../bdf2u8g/bdf2u8g -l 0 -u 1 -b 0 -e 255  ../bdf/unifont.bdf u8g_font_unifont u8g_font_unifont.c > /dev/null
../bdf2u8g/bdf2u8g -l 0 -u 1 -b 32 -e 127  ../bdf/unifont.bdf u8g_font_unifontr u8g_font_unifontr.c > /dev/null
../bdf2u8g/bdf2u8g -l 2 -u 3 -b 0 -e 255  ../bdf/unifont.bdf u8g_font_unifont_2_3 u8g_font_unifont_2_3.c > /dev/null
../bdf2u8g/bdf2u8g -l 4 -u 5 -b 0 -e 255  ../bdf/unifont.bdf u8g_font_unifont_4_5 u8g_font_unifont_4_5.c > /dev/null
../bdf2u8g/bdf2u8g -l 18 -u 19 -b 0 -e 255 ../bdf/unifont.bdf u8g_font_unifont_18_19 u8g_font_unifont_18_19.c > /dev/null
../bdf2u8g/bdf2u8g -l 72 -u 73 -b 0 -e 255 ../bdf/unifont.bdf u8g_font_unifont_72_73 u8g_font_unifont_72_73.c > /dev/null
../bdf2u8g/bdf2u8g -l 67 -u 75 -b 16 -e 255 ../bdf/unifont.bdf u8g_font_unifont_67_75 u8g_font_unifont_67_75.c > /dev/null
../bdf2u8g/bdf2u8g -l 75 -b 32 -e 79 ../bdf/unifont.bdf u8g_font_unifont_75r u8g_font_unifont_75r.c > /dev/null
../bdf2u8g/bdf2u8g -l 78 -u 79 -b 1 -e 255 ../bdf/unifont.bdf u8g_font_unifont_78_79 u8g_font_unifont_78_79.c > /dev/null
../bdf2u8g/bdf2u8g -l 86 -u 87 -s 32 -b 32 -e 116 ../bdf/unifont.bdf u8g_font_unifont_86 u8g_font_unifont_86.c > /dev/null
../bdf2u8g/bdf2u8g -l 77 -u 87 -s 32 -b 32 -e 99 ../bdf/unifont.bdf u8g_font_unifont_77 u8g_font_unifont_77.c > /dev/null
../bdf2u8g/bdf2u8g -l 76 -u 87 -s 32 -b 32 -e 159  ../bdf/unifont.bdf u8g_font_unifont_76 u8g_font_unifont_76.c > /dev/null
../bdf2u8g/bdf2u8g -l 8 -u 9 -b 0 -e 255 ../bdf/unifont.bdf u8g_font_unifont_8_9 u8g_font_unifont_8_9.c > /dev/null
../bdf2u8g/bdf2u8g -l 0 -u 8 -S 32  ../bdf/unifont.bdf u8g_font_unifont_0_8 u8g_font_unifont_0_8.c > /dev/null
../bdf2u8g/bdf2u8g -l 12 -u 13 -b 0 -e 255 ../bdf/unifont.bdf u8g_font_unifont_12_13 u8g_font_unifont_12_13.c > /dev/null

echo "adobe courB 08"
../bdf2u8g/bdf2u8g ../bdf/courB08.bdf u8g_font_courB08 u8g_font_courb08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courB08.bdf u8g_font_courB08r u8g_font_courb08r.c > /dev/null
echo "adobe courB 10"
../bdf2u8g/bdf2u8g ../bdf/courB10.bdf u8g_font_courB10 u8g_font_courb10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courB10.bdf u8g_font_courB10r u8g_font_courb10r.c > /dev/null
echo "adobe courB 12"
../bdf2u8g/bdf2u8g ../bdf/courB12.bdf u8g_font_courB12 u8g_font_courb12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courB12.bdf u8g_font_courB12r u8g_font_courb12r.c > /dev/null
echo "adobe courB 14"
../bdf2u8g/bdf2u8g ../bdf/courB14.bdf u8g_font_courB14 u8g_font_courb14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courB14.bdf u8g_font_courB14r u8g_font_courb14r.c > /dev/null
echo "adobe courB 18"
../bdf2u8g/bdf2u8g ../bdf/courB18.bdf u8g_font_courB18 u8g_font_courb18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courB18.bdf u8g_font_courB18r u8g_font_courb18r.c > /dev/null
echo "adobe courB 24"
../bdf2u8g/bdf2u8g ../bdf/courB24.bdf u8g_font_courB24 u8g_font_courb24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courB24.bdf u8g_font_courB24r u8g_font_courb24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58 ../bdf/courB24.bdf u8g_font_courB24n u8g_font_courb4n.c > /dev/null

echo "adobe courR"
../bdf2u8g/bdf2u8g ../bdf/courR08.bdf u8g_font_courR08 u8g_font_courr08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courR08.bdf u8g_font_courR08r u8g_font_courr08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/courR10.bdf u8g_font_courR10 u8g_font_courr10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courR10.bdf u8g_font_courR10r u8g_font_courr10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/courR12.bdf u8g_font_courR12 u8g_font_courr12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courR12.bdf u8g_font_courR12r u8g_font_courr12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/courR14.bdf u8g_font_courR14 u8g_font_courr14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courR14.bdf u8g_font_courR14r u8g_font_courr14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/courR18.bdf u8g_font_courR18 u8g_font_courr18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courR18.bdf u8g_font_courR18r u8g_font_courr18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/courR24.bdf u8g_font_courR24 u8g_font_courr24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/courR24.bdf u8g_font_courR24r u8g_font_courr24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58 ../bdf/courR24.bdf u8g_font_courR24n u8g_font_courr24n.c > /dev/null

echo "adobe helvB"
../bdf2u8g/bdf2u8g ../bdf/helvB08.bdf u8g_font_helvB08 u8g_font_helvb08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvB08.bdf u8g_font_helvB08r u8g_font_helvb08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvB10.bdf u8g_font_helvB10 u8g_font_helvb10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvB10.bdf u8g_font_helvB10r u8g_font_helvb10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvB12.bdf u8g_font_helvB12 u8g_font_helvb12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvB12.bdf u8g_font_helvB12r u8g_font_helvb12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvB14.bdf u8g_font_helvB14 u8g_font_helvb14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvB14.bdf u8g_font_helvB14r u8g_font_helvb14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvB18.bdf u8g_font_helvB18 u8g_font_helvb18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvB18.bdf u8g_font_helvB18r u8g_font_helvb18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvB24.bdf u8g_font_helvB24 u8g_font_helvb24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvB24.bdf u8g_font_helvB24r u8g_font_helvb24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58  ../bdf/helvB24.bdf u8g_font_helvB24n u8g_font_helvb24n.c > /dev/null

echo "adobe helvR"
../bdf2u8g/bdf2u8g ../bdf/helvR08.bdf u8g_font_helvR08 u8g_font_helvr08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvR08.bdf u8g_font_helvR08r u8g_font_helvr08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvR10.bdf u8g_font_helvR10 u8g_font_helvr10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvR10.bdf u8g_font_helvR10r u8g_font_helvr10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvR12.bdf u8g_font_helvR12 u8g_font_helvr12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvR12.bdf u8g_font_helvR12r u8g_font_helvr12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvR14.bdf u8g_font_helvR14 u8g_font_helvr14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvR14.bdf u8g_font_helvR14r u8g_font_helvr14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvR18.bdf u8g_font_helvR18 u8g_font_helvr18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvR18.bdf u8g_font_helvR18r u8g_font_helvr18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/helvR24.bdf u8g_font_helvR24 u8g_font_helvr24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/helvR24.bdf u8g_font_helvR24r u8g_font_helvr24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58  ../bdf/helvR24.bdf u8g_font_helvR24n u8g_font_helvr24n.c > /dev/null

echo "adobe ncenB"
../bdf2u8g/bdf2u8g ../bdf/ncenB08.bdf u8g_font_ncenB08 u8g_font_ncenb08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenB08.bdf u8g_font_ncenB08r u8g_font_ncenb08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenB10.bdf u8g_font_ncenB10 u8g_font_ncenb10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenB10.bdf u8g_font_ncenB10r u8g_font_ncenb10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenB12.bdf u8g_font_ncenB12 u8g_font_ncenb12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenB12.bdf u8g_font_ncenB12r u8g_font_ncenb12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenB14.bdf u8g_font_ncenB14 u8g_font_ncenb14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenB14.bdf u8g_font_ncenB14r u8g_font_ncenb14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenB18.bdf u8g_font_ncenB18 u8g_font_ncenb18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenB18.bdf u8g_font_ncenB18r u8g_font_ncenb18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenB24.bdf u8g_font_ncenB24 u8g_font_ncenb24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenB24.bdf u8g_font_ncenB24r u8g_font_ncenb24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58  ../bdf/ncenB24.bdf u8g_font_ncenB24n u8g_font_ncenb24n.c > /dev/null

echo "adobe ncenR"
../bdf2u8g/bdf2u8g ../bdf/ncenR08.bdf u8g_font_ncenR08 u8g_font_ncenr08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenR08.bdf u8g_font_ncenR08r u8g_font_ncenr08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenR10.bdf u8g_font_ncenR10 u8g_font_ncenr10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenR10.bdf u8g_font_ncenR10r u8g_font_ncenr10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenR12.bdf u8g_font_ncenR12 u8g_font_ncenr12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenR12.bdf u8g_font_ncenR12r u8g_font_ncenr12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenR14.bdf u8g_font_ncenR14 u8g_font_ncenr14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenR14.bdf u8g_font_ncenR14r u8g_font_ncenr14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenR18.bdf u8g_font_ncenR18 u8g_font_ncenr18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenR18.bdf u8g_font_ncenR18r u8g_font_ncenr18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/ncenR24.bdf u8g_font_ncenR24 u8g_font_ncenr24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/ncenR24.bdf u8g_font_ncenR24r u8g_font_ncenr24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58  ../bdf/ncenR24.bdf u8g_font_ncenR24n u8g_font_ncenr24n.c > /dev/null


echo "adobe timB"
../bdf2u8g/bdf2u8g ../bdf/timB08.bdf u8g_font_timB08 u8g_font_timb08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timB08.bdf u8g_font_timB08r u8g_font_timb08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timB10.bdf u8g_font_timB10 u8g_font_timb10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timB10.bdf u8g_font_timB10r u8g_font_timb10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timB12.bdf u8g_font_timB12 u8g_font_timb12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timB12.bdf u8g_font_timB12r u8g_font_timb12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timB14.bdf u8g_font_timB14 u8g_font_timb14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timB14.bdf u8g_font_timB14r u8g_font_timb14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timB18.bdf u8g_font_timB18 u8g_font_timb18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timB18.bdf u8g_font_timB18r u8g_font_timb18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timB24.bdf u8g_font_timB24 u8g_font_timb24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timB24.bdf u8g_font_timB24r u8g_font_timb24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58  ../bdf/timB24.bdf u8g_font_timB24n u8g_font_timb24n.c > /dev/null

echo "adobe timR"
../bdf2u8g/bdf2u8g ../bdf/timR08.bdf u8g_font_timR08 u8g_font_timr08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timR08.bdf u8g_font_timR08r u8g_font_timr08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timR10.bdf u8g_font_timR10 u8g_font_timr10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timR10.bdf u8g_font_timR10r u8g_font_timr10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timR12.bdf u8g_font_timR12 u8g_font_timr12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timR12.bdf u8g_font_timR12r u8g_font_timr12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timR14.bdf u8g_font_timR14 u8g_font_timr14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timR14.bdf u8g_font_timR14r u8g_font_timr14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timR18.bdf u8g_font_timR18 u8g_font_timr18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timR18.bdf u8g_font_timR18r u8g_font_timr18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/timR24.bdf u8g_font_timR24 u8g_font_timr24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/timR24.bdf u8g_font_timR24r u8g_font_timr24r.c > /dev/null
../bdf2u8g/bdf2u8g  -b 42 -e 58  ../bdf/timR24.bdf u8g_font_timR24n u8g_font_timr24n.c > /dev/null

echo "adobe symb"
../bdf2u8g/bdf2u8g ../bdf/symb08.bdf u8g_font_symb08 u8g_font_symb08.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/symb08.bdf u8g_font_symb08r u8g_font_symb08r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/symb10.bdf u8g_font_symb10 u8g_font_symb10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/symb10.bdf u8g_font_symb10r u8g_font_symb10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/symb12.bdf u8g_font_symb12 u8g_font_symb12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/symb12.bdf u8g_font_symb12r u8g_font_symb12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/symb14.bdf u8g_font_symb14 u8g_font_symb14.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/symb14.bdf u8g_font_symb14r u8g_font_symb14r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/symb18.bdf u8g_font_symb18 u8g_font_symb18.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/symb18.bdf u8g_font_symb18r u8g_font_symb18r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/symb24.bdf u8g_font_symb24 u8g_font_symb24.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/symb24.bdf u8g_font_symb24r u8g_font_symb24r.c > /dev/null

echo "profont"
../bdf2u8g/bdf2u8g ../bdf/profont10.bdf u8g_font_profont10 u8g_font_profont10.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/profont10.bdf u8g_font_profont10r u8g_font_profont10r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/profont11.bdf u8g_font_profont11 u8g_font_profont11.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/profont11.bdf u8g_font_profont11r u8g_font_profont11r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/profont12.bdf u8g_font_profont12 u8g_font_profont12.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/profont12.bdf u8g_font_profont12r u8g_font_profont12r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/profont15.bdf u8g_font_profont15 u8g_font_profont15.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/profont15.bdf u8g_font_profont15r u8g_font_profont15r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/profont17.bdf u8g_font_profont17 u8g_font_profont17.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/profont17.bdf u8g_font_profont17r u8g_font_profont17r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/profont22.bdf u8g_font_profont22 u8g_font_profont22.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/profont22.bdf u8g_font_profont22r u8g_font_profont22r.c > /dev/null
../bdf2u8g/bdf2u8g ../bdf/profont29.bdf u8g_font_profont29 u8g_font_profont29.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127 ../bdf/profont29.bdf u8g_font_profont29r u8g_font_profont29r.c > /dev/null


echo "contributed"
../bdf2u8g/bdf2u8g  -b 32 -e 127  ../bdf/freedoomr25n.bdf u8g_font_freedoomr25n u8g_font_freedoomr25n.c > /dev/null
../bdf2u8g/bdf2u8g  -b 32 -e 127  ../bdf/freedoomr10r.bdf u8g_font_freedoomr10r u8g_font_freedoomr10r.c > /dev/null


echo "fontstruct"
./do_u8g_fontsize.sh 8 ../ttf/p01type.ttf p01type
./do_u8g_fontsize.sh 8 ../ttf/lucasfont_alternate.ttf lucasfont_alternate
#./do_u8g_fontsize.sh 4 ../ttf/fs_onebrickpixelfont.ttf fs_onebrickpixelfont
./do_u8g_fontsize.sh 8 ../ttf/chikita.ttf chikita
./do_u8g_fontsize.sh 8 ../ttf/pixelle_micro.ttf pixelle_micro
./do_u8g_fontsize.sh 8 ../ttf/trixel_square.ttf trixel_square
./do_u8g_fontsize.sh 16 ../ttf/robot_de_niro.ttf robot_de_niro
./do_u8g_fontsize.sh 8 ../ttf/baby.ttf baby
./do_u8g_fontsize.sh 8 ../ttf/blipfest_07.ttf blipfest_07



./do_u8g_fontsize.sh 15 ../ttf/GenBasR.ttf gdr9
./do_u8g_fontsize.sh 17 ../ttf/GenBasR.ttf gdr10
./do_u8g_fontsize.sh 18 ../ttf/GenBasR.ttf gdr11
./do_u8g_fontsize.sh 19 ../ttf/GenBasR.ttf gdr12
./do_u8g_fontsize.sh 23 ../ttf/GenBasR.ttf gdr14
./do_u8g_fontsize.sh 27 ../ttf/GenBasR.ttf gdr17
./do_u8g_fontsize.sh 32 ../ttf/GenBasR.ttf gdr20
./do_u8g_fontsize.sh 40 ../ttf/GenBasR.ttf gdr25
./do_u8g_fontsize.sh 48 ../ttf/GenBasR.ttf gdr30
  
./do_u8g_fontsize.sh 18 ../ttf/GenBasB.ttf gdb11
./do_u8g_fontsize.sh 19 ../ttf/GenBasB.ttf gdb12
./do_u8g_fontsize.sh 23 ../ttf/GenBasB.ttf gdb14
./do_u8g_fontsize.sh 27 ../ttf/GenBasB.ttf gdb17
./do_u8g_fontsize.sh 32 ../ttf/GenBasB.ttf gdb20
./do_u8g_fontsize.sh 40 ../ttf/GenBasB.ttf gdb25
./do_u8g_fontsize.sh 48 ../ttf/GenBasB.ttf gdb30

./do_u8g_fontsize_a.sh 16 ../ttf/FreeUniversal-Bold.ttf fub11
./do_u8g_fontsize_a.sh 20 ../ttf/FreeUniversal-Bold.ttf fub14
./do_u8g_fontsize_a.sh 23 ../ttf/FreeUniversal-Bold.ttf fub17
./do_u8g_fontsize_a.sh 27 ../ttf/FreeUniversal-Bold.ttf fub20
./do_u8g_fontsize_a.sh 34 ../ttf/FreeUniversal-Bold.ttf fub25
./do_u8g_fontsize_a.sh 40 ../ttf/FreeUniversal-Bold.ttf fub30
./do_u8g_fontsize_a_n.sh 49 ../ttf/FreeUniversal-Bold.ttf fub35n
./do_u8g_fontsize_a_n.sh 58 ../ttf/FreeUniversal-Bold.ttf fub42n
./do_u8g_fontsize_a_n.sh 68 ../ttf/FreeUniversal-Bold.ttf fub49n
  
./do_u8g_fontsize_a.sh 15 ../ttf/FreeUniversal-Regular.ttf fur11
./do_u8g_fontsize_a.sh 19 ../ttf/FreeUniversal-Regular.ttf fur14
./do_u8g_fontsize_a.sh 23 ../ttf/FreeUniversal-Regular.ttf fur17
./do_u8g_fontsize_a.sh 28 ../ttf/FreeUniversal-Regular.ttf fur20
./do_u8g_fontsize_a.sh 34 ../ttf/FreeUniversal-Regular.ttf fur25
./do_u8g_fontsize_a.sh 40 ../ttf/FreeUniversal-Regular.ttf fur30
./do_u8g_fontsize_a_n.sh 48 ../ttf/FreeUniversal-Regular.ttf fur35n
./do_u8g_fontsize_a_n.sh 58 ../ttf/FreeUniversal-Regular.ttf fur42n
./do_u8g_fontsize_a_n.sh 68 ../ttf/FreeUniversal-Regular.ttf fur49n

./do_u8g_fontsize_a.sh 25 ../ttf/OldStandard-Bold.ttf osb18
./do_u8g_fontsize_a.sh 28 ../ttf/OldStandard-Bold.ttf osb21
./do_u8g_fontsize_a.sh 34 ../ttf/OldStandard-Bold.ttf osb26
./do_u8g_fontsize_a.sh 38 ../ttf/OldStandard-Bold.ttf osb29
./do_u8g_fontsize_a.sh 48 ../ttf/OldStandard-Bold.ttf osb35
#./do_u8g_fontsize_a.sh 55 ../ttf/OldStandard-Bold.ttf osb41

./do_u8g_fontsize_a.sh 26 ../ttf/OldStandard-Regular.ttf osr18
./do_u8g_fontsize_a.sh 29 ../ttf/OldStandard-Regular.ttf osr21
./do_u8g_fontsize_a.sh 36 ../ttf/OldStandard-Regular.ttf osr26
./do_u8g_fontsize_a.sh 41 ../ttf/OldStandard-Regular.ttf osr29
./do_u8g_fontsize_a.sh 49 ../ttf/OldStandard-Regular.ttf osr35
#./do_u8g_fontsize_a.sh 57 ../ttf/OldStandard-Reglar.ttf osr41

echo "04B"
#./do_u8g_fontsize.sh 7 ../ttf/7px4bus.ttf 7px4bus              # status nicht ganz klar
./do_u8g_fontsize_f1.sh 8 ../ttf/04B_03B_.TTF 04b_03b 
./do_u8g_fontsize_f1.sh 8 ../ttf/04B_03__.TTF 04b_03 
./do_u8g_fontsize_f1.sh 8 ../ttf/04B_24__.TTF 04b_24 

echo "orgdot"
./do_u8g_fontsize.sh 8 ../ttf/TEACPSS_.TTF tpss 
./do_u8g_fontsize.sh 8 ../ttf/TEACPSSB.TTF tpssb 
./do_u8g_fontsize_f1.sh 8 ../ttf/ORG_V01_.TTF orgv01 
./do_u8g_fontsize_f1.sh 8 ../ttf/FIXED_V0.TTF fixed_v0 




echo "copy fonts..."
cp u8g_font_*.c ../../../fntsrc/.

