cd u8g_arm
mkdir $1
cd $1
mkdir common
cp ../../../../../sys/arm/$1/common/*.[hcS] ./common/.
cp ../../../../../sys/arm/$1/common/*.ld ./common/.
mkdir hello_world
cp ../../../../../sys/arm/examples/hello_world/*.c ./hello_world/.
cp ../../Makefile.* ./hello_world/.
mkdir graphics_test
cp ../../../../../sys/arm/examples/graphics_test/*.c ./graphics_test/.
cp ../../Makefile.* ./graphics_test/.
mkdir u8g_logo
cp ../../../../../sys/arm/examples/u8g_logo/*.c ./u8g_logo/.
cp ../../Makefile.* ./u8g_logo/.
mkdir menu
cp ../../../../../sys/arm/examples/menu/*.c ./menu/.
cp ../../Makefile.* ./menu/.


