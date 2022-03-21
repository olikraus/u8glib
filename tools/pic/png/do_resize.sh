#!/bin/bash
rm *-44.png *-28.png *-28.png
for i in $( ls *.png); do
    echo convert: ${i%.png}
#    convert $i -gravity center -extent 48x48 -filter Hermite -resize 44x44 -threshold 50% ${i%.png}-44.png
    convert $i -gravity center -extent 48x48 -filter Triangle -resize 28x28 -threshold 50% ${i%.png}-28.xbm
    convert $i -gravity center -extent 48x48 -filter Triangle -resize 28x28 -threshold 50% ${i%.png}-28.png
#    convert $i -gravity center -extent 48x48 -resize 28x28 -monochrome ${i%.png}-28.png
done
