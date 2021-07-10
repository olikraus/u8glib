mkdir ../../../../U8glib_Arduino/examples/HelloWorld
mkdir ../../../../U8glib_Arduino/examples/Bitmap
mkdir ../../../../U8glib_Arduino/examples/Console
#mkdir ../../../../U8glib_Arduino/examples/Color
mkdir ../../../../U8glib_Arduino/examples/U8gLogo
mkdir ../../../../U8glib_Arduino/examples/Rotation
mkdir ../../../../U8glib_Arduino/examples/PrintTest
mkdir ../../../../U8glib_Arduino/examples/F
mkdir ../../../../U8glib_Arduino/examples/FPS
mkdir ../../../../U8glib_Arduino/examples/TextRotX
mkdir ../../../../U8glib_Arduino/examples/XBM
mkdir ../../../../U8glib_Arduino/examples/Chess
mkdir ../../../../U8glib_Arduino/examples/GraphicsTest
mkdir ../../../../U8glib_Arduino/examples/Menu
mkdir ../../../../U8glib_Arduino/examples/Scale
mkdir ../../../../U8glib_Arduino/examples/Touch4WSetup
mkdir ../../../../U8glib_Arduino/examples/Touch4WTest
mkdir ../../../../U8glib_Arduino/examples/A2Printer
#mkdir ../../../../U8glib_Arduino/utility
cp ../../../ChangeLog ./../../../../U8glib_Arduino/extras/.
# cp ../../../license.txt ./../../../../U8glib_Arduino/.
cp INSTALL.TXT ./../../../../U8glib_Arduino/extras/.
cp library.properties ../../../../U8glib_Arduino/.
cp ../../../cppsrc/*.cpp ./../../../../U8glib_Arduino/src/.
cp ../../../cppsrc/*.h ./../../../../U8glib_Arduino/src/.
sed -i 's|u8g.h|clib/u8g.h|g' ./../../../../U8glib_Arduino/src/U8glib.h
cp ../../../csrc/*.c ./../../../../U8glib_Arduino/src/clib/.
cp ../../../csrc/*.h ./../../../../U8glib_Arduino/src/clib/.
cp ../../../sfntsrc/*.c ./../../../../U8glib_Arduino/src/clib/.
cp ../../../sys/arduino/HelloWorld/HelloWorld.pde ./../../../../U8glib_Arduino/examples/HelloWorld/HelloWorld.ino
cp ../../../sys/arduino/Bitmap/Bitmap.pde ./../../../../U8glib_Arduino/examples/Bitmap/Bitmap.ino
cp ../../../sys/arduino/Console/Console.pde ./../../../../U8glib_Arduino/examples/Console/Console.ino
# cp ../../../sys/arduino/Color/*.pde ./../../../../U8glib_Arduino/examples/Color/.
cp ../../../sys/arduino/U8gLogo/U8gLogo.pde ./../../../../U8glib_Arduino/examples/U8gLogo/U8gLogo.ino
cp ../../../sys/arduino/Rotation/Rotation.pde ./../../../../U8glib_Arduino/examples/Rotation/Rotation.ino
cp ../../../sys/arduino/PrintTest/PrintTest.pde ./../../../../U8glib_Arduino/examples/PrintTest/PrintTest.ino
cp ../../../sys/arduino/F/F.pde ./../../../../U8glib_Arduino/examples/F/F.ino
cp ../../../sys/arduino/FPS/FPS.pde ./../../../../U8glib_Arduino/examples/FPS/FPS.ino
cp ../../../sys/arduino/TextRotX/TextRotX.pde ./../../../../U8glib_Arduino/examples/TextRotX/TextRotX.ino
cp ../../../sys/arduino/XBM/XBM.pde ./../../../../U8glib_Arduino/examples/XBM/XBM.ino
cp ../../../sys/arduino/Chess/Chess.pde ./../../../../U8glib_Arduino/examples/Chess/Chess.ino
cp ../../../sys/arduino/GraphicsTest/GraphicsTest.pde ./../../../../U8glib_Arduino/examples/GraphicsTest/GraphicsTest.ino
cp ../../../sys/arduino/Menu/Menu.pde ./../../../../U8glib_Arduino/examples/Menu/Menu.ino
cp ../../../sys/arduino/Scale/Scale.pde ./../../../../U8glib_Arduino/examples/Scale/Scale.ino
cp ../../../sys/arduino/Touch4WSetup/Touch4WSetup.pde ./../../../../U8glib_Arduino/examples/Touch4WSetup/Touch4WSetup.ino
cp ../../../sys/arduino/Touch4WTest/Touch4WTest.pde ./../../../../U8glib_Arduino/examples/Touch4WTest/Touch4WTest.ino
cp ../../../sys/arduino/A2Printer/A2Printer.pde ./../../../../U8glib_Arduino/examples/A2Printer/A2Printer.ino
# sed -i 's|U8glib.h|utility/U8glib.h|g' ./../../../../U8glib_Arduino/examples/HelloWorld/*.pde


# rename to .ino
# find . -name "*.pde" -exec /bin/sh -c 'f={}; mv ${f} ${f%.*}.ino' \;

cd ../../../../U8glib_Arduino

ver=`../u8glib/tools/release/print_release.sh`

sed -i -e "s/version=.*/version=${ver}/" library.properties


git commit -a -m `../u8glib/tools/release/print_release.sh`
git push

echo now create a release in gitub for U8glib_Arduino, tag/name = ${ver}
# Relases in github:
# Tag: 1.02pre3
# Release  name: 1.02pre3


