rm -rf u8glib
mkdir u8glib
mkdir u8glib/src
mkdir u8glib/examples
mkdir u8glib/examples/hello_world

cp ../../../ChangeLog ./u8glib/.
cp ../../../license.txt ./u8glib/.

cp ../../../csrc/*.c ./u8glib/src/.
cp ../../../csrc/*.h ./u8glib/src/.
cp ../../../sfntsrc/*.c ./u8glib/src/.
cp ../../../sys/atmega/hello_world/*.c ./u8glib/examples/hello_world/.


chmod -R og=u u8glib
zip -r u8glib_avr_`../print_release.sh`.zip u8glib
#cd u8glib 
#zip -r ../u8glib_avr_`../../print_release.sh`.zip *
#cd ..