#!/bin/sh

PROGNAME="$0"
#DN_EXEC=`echo "${PROGNAME}" | ${EXEC_AWK} -F/ '{b=$1; for (i=2; i < NF; i ++) {b=b "/" $(i)}; print b}'`
DN_EXEC=`dirname "${PROGNAME}"`
if [ ! "${DN_EXEC}" = "" ]; then
    DN_EXEC="${DN_EXEC}/"
else
    DN_EXEC="./"
fi

${DN_EXEC}autoclean.sh

rm -f configure

rm -f Makefile.in

rm -f config.guess
rm -f config.sub
rm -f install-sh
rm -f missing
rm -f depcomp

# install libs
#which apt-get
#if [ "$?" = "0" ]; then
    #sudo apt-get install -y libxml2-dev libxslt-dev libicu-dev
    ## for traceback
    #sudo apt-get install -y binutils-dev libiberty-dev
    ## for doxygen
    #sudo apt-get install -y graphviz doxygen texlive-full
#fi

#which yum
#if [ "$?" = "0" ]; then
    #sudo yum install -y libxml2-devel libxslt-devel libicu-devel
#if

if [ 0 = 1 ]; then
autoscan
else
#cd pflib && ${DN_EXEC}autogen.sh && cd ..

touch NEWS
touch README
touch AUTHORS
touch ChangeLog
touch config.h.in

libtoolize --force --copy --install --automake
aclocal
#automake -ac
automake --copy --add-missing --gnu
autoconf

autoreconf # run twice to get rid of 'ltmain.sh not found'
autoreconf

if [ 1 = 1 ]; then
rm -rf build
mkdir -p build
cd build
fi

#${DN_EXEC}configure --enable-debug
#./configure --enable-debug
#make clean
#make

fi
