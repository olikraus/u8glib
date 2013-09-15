pushd .
cd ..
cd ..
cd ..
cd sys
cd arm
find -type d -exec sh -c "cd {} && make clean" \;
popd
