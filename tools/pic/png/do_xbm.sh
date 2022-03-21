#!/bin/bash
for i in $( ls *.png); do
    echo png: ${i%.png}
    convert $i ../xbm/${i%.png}.xbm
    sed -i "y/-/_/" ../xbm/${i%.png}.xbm
    sed -i "s/] = {/] U8G_PROGMEM = {/" ../xbm/${i%.png}.xbm
done
