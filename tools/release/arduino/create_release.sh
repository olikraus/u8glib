rm -rf libraries
mkdir libraries
mkdir libraries/U8glib
mkdir libraries/U8glib/examples
mkdir libraries/U8glib/examples/HelloWorld
mkdir libraries/U8glib/examples/Bitmap
mkdir libraries/U8glib/examples/Console
mkdir libraries/U8glib/examples/Color
mkdir libraries/U8glib/examples/U8gLogo
mkdir libraries/U8glib/examples/Rotation
mkdir libraries/U8glib/examples/PrintTest
mkdir libraries/U8glib/examples/F
mkdir libraries/U8glib/examples/FPS
mkdir libraries/U8glib/examples/TextRotX
mkdir libraries/U8glib/examples/XBM
mkdir libraries/U8glib/examples/Chess
mkdir libraries/U8glib/examples/GraphicsTest
mkdir libraries/U8glib/examples/Menu
mkdir libraries/U8glib/examples/Scale
mkdir libraries/U8glib/examples/Touch4WSetup
mkdir libraries/U8glib/examples/Touch4WTest
mkdir libraries/U8glib/examples/A2Printer
mkdir libraries/U8glib/utility
cp ../../../ChangeLog ./libraries/U8glib/.
cp ../../../license.txt ./libraries/U8glib/.
cp INSTALL.TXT ./libraries/U8glib/.
cp ../../../cppsrc/*.cpp ./libraries/U8glib/.
cp ../../../cppsrc/*.h ./libraries/U8glib/.
sed -i 's|u8g.h|utility/u8g.h|g' ./libraries/U8glib/U8glib.h
cp ../../../csrc/*.c ./libraries/U8glib/utility/.
cp ../../../csrc/*.h ./libraries/U8glib/utility/.
cp ../../../sfntsrc/*.c ./libraries/U8glib/utility/.
cp ../../../sys/arduino/HelloWorld/*.pde ./libraries/U8glib/examples/HelloWorld/.
cp ../../../sys/arduino/Bitmap/*.pde ./libraries/U8glib/examples/Bitmap/.
cp ../../../sys/arduino/Console/*.pde ./libraries/U8glib/examples/Console/.
cp ../../../sys/arduino/Color/*.pde ./libraries/U8glib/examples/Color/.
cp ../../../sys/arduino/U8gLogo/*.pde ./libraries/U8glib/examples/U8gLogo/.
cp ../../../sys/arduino/Rotation/*.pde ./libraries/U8glib/examples/Rotation/.
cp ../../../sys/arduino/PrintTest/*.pde ./libraries/U8glib/examples/PrintTest/.
cp ../../../sys/arduino/F/*.pde ./libraries/U8glib/examples/F/.
cp ../../../sys/arduino/FPS/*.pde ./libraries/U8glib/examples/FPS/.
cp ../../../sys/arduino/TextRotX/*.pde ./libraries/U8glib/examples/TextRotX/.
cp ../../../sys/arduino/XBM/*.pde ./libraries/U8glib/examples/XBM/.
cp ../../../sys/arduino/Chess/*.pde ./libraries/U8glib/examples/Chess/.
cp ../../../sys/arduino/GraphicsTest/*.pde ./libraries/U8glib/examples/GraphicsTest/.
cp ../../../sys/arduino/Menu/*.pde ./libraries/U8glib/examples/Menu/.
cp ../../../sys/arduino/Scale/*.pde ./libraries/U8glib/examples/Scale/.
cp ../../../sys/arduino/Touch4WSetup/*.pde ./libraries/U8glib/examples/Touch4WSetup/.
cp ../../../sys/arduino/Touch4WTest/*.pde ./libraries/U8glib/examples/Touch4WTest/.
cp ../../../sys/arduino/A2Printer/*.pde ./libraries/U8glib/examples/A2Printer/.
# sed -i 's|U8glib.h|utility/U8glib.h|g' ./libraries/U8glib/examples/HelloWorld/*.pde

# rename to .ino
find . -name "*.pde" -exec /bin/sh -c 'f={}; mv ${f} ${f%.*}.ino' \;


chmod -R og=u libraries
cd libraries 
zip -r ../u8glib_arduino_`../../print_release.sh`.zip *
cd ..

