rm -rf u8glib
mkdir u8glib
mkdir u8glib/src
mkdir u8glib/examples
mkdir u8glib/examples/hello_world
#cp Makefile u8glib/examples/hello_world
mkdir u8glib/examples/graphics_test
#cp Makefile u8glib/examples/graphics_test

cp ../../../ChangeLog ./u8glib/.
cp ../../../license.txt ./u8glib/.
cp INSTALL.TXT ./u8glib/.

cp ../../../csrc/*.c ./u8glib/src/.
cp ../../../csrc/*.h ./u8glib/src/.
cp ../../../sfntsrc/*.c ./u8glib/src/.
cp ../../../sys/msp430/hello_world/*.c ./u8glib/examples/hello_world/.
cp ../../../sys/msp430/graphics_test/*.c ./u8glib/examples/graphics_test/.


chmod -R og=u u8glib
rm u8glib_msp430_`../print_release.sh`.zip
zip -r u8glib_msp430_`../print_release.sh`.zip u8glib
#cd u8glib 
#zip -r ../u8glib_avr_`../../print_release.sh`.zip *
#cd ..