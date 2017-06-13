#!/bin/bash
#
# ykam24cmd command application build script

rm -rf hidapi

echo "Checking for git..."
command -v git >/dev/null 2>&1 || { echo >&2 "Git is required and is not installed. Aborting."; exit 1; }

echo "Fetching latest version of hidapi..."
git clone git://github.com/signal11/hidapi.git

echo "Building hidapi..."
make --directory=hidapi/linux -f Makefile-manual
cp -fv hidapi/linux/libhidapi-hidraw.so src/linux/

make --directory=hidapi/libusb -f Makefile-manual
cp -fv hidapi/libusb/libhidapi-libusb.so src/linux/

echo "Configuring ykam24cmd app files..."

echo "#ifndef PLATFORMDEFS_H" > src/platformdefs.h
echo "#define PLATFORMDEFS_H" >> src/platformdefs.h
#echo "#define LINUX" >> src/platformdefs.h
echo "#endif" >> src/platformdefs.h

echo "Building ykam24cmd command..."
make

