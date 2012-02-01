rm -rf libraries
mkdir libraries
mkdir libraries/U8glib
mkdir libraries/U8glib/examples
mkdir libraries/U8glib/examples/HelloWorld
mkdir libraries/U8glib/examples/Bitmap
mkdir libraries/U8glib/examples/Console
mkdir libraries/U8glib/examples/U8gLogo
mkdir libraries/U8glib/examples/Rotation
mkdir libraries/U8glib/utility
cp ../../../ChangeLog ./libraries/U8glib/.
cp ../../../license.txt ./libraries/U8glib/.
cp ../../../cppsrc/*.cpp ./libraries/U8glib/.
cp ../../../cppsrc/*.h ./libraries/U8glib/.
sed -i 's|u8g.h|utility/u8g.h|g' ./libraries/U8glib/U8glib.h
cp ../../../csrc/*.c ./libraries/U8glib/utility/.
cp ../../../csrc/*.h ./libraries/U8glib/utility/.
cp ../../../sfntsrc/*.c ./libraries/U8glib/utility/.
cp ../../../sys/arduino/HelloWorld/*.pde ./libraries/U8glib/examples/HelloWorld/.
cp ../../../sys/arduino/Bitmap/*.pde ./libraries/U8glib/examples/Bitmap/.
cp ../../../sys/arduino/Console/*.pde ./libraries/U8glib/examples/Console/.
cp ../../../sys/arduino/U8gLogo/*.pde ./libraries/U8glib/examples/U8gLogo/.
cp ../../../sys/arduino/Rotation/*.pde ./libraries/U8glib/examples/Rotation/.
# sed -i 's|U8glib.h|utility/U8glib.h|g' ./libraries/U8glib/examples/HelloWorld/*.pde


chmod -R og=u libraries
cd libraries 
zip -r ../u8glib_arduino_`../../print_release.sh`.zip *
cd ..