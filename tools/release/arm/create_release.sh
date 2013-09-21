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
mkdir src
cd src
cp ../../../../../csrc/*.[hc] .
cp ../../../../../sfntsrc/*.[hc] .
cd ..
cd ..
./sub_create.sh	lpc1114
