#!/bin/bash

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
#../bdf2u8g/bdf2u8g -f 1 -b 42 -e 57 ../bdf/4x6.bdf u8g_font_4x6n u8g_font_4x6n.c  > /dev/null
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

