# pushd .
# cd ..
# cd ..
# cd ..
# cd sys
# cd arm
# ind -type d -exec sh -c "cd {} && make clean" \;
# popd
rm -rf u8g_arm
mkdir u8g_arm
cd u8g_arm
cp ../INSTALL .
mkdir src
cd src
cp ../../../../../csrc/*.[hc] .
cp ../../../../../sfntsrc/*.[hc] .
cd ..
cd ..
./sub_create.sh	lpc1114
./sub_create.sh	lpc1226


chmod -R og+r u8g_arm
cd u8g_arm 
zip -r ../u8glib_arm_`../../print_release.sh`.zip *
cd ..

