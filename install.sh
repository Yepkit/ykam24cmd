#!/bin/bash

echo installing ykam24cmd command...
sudo cp -f bin/ykam24cmd /usr/bin

echo installing shared libraries...
sudo cp -f ykam24cmd/linux/libhidapi-hidraw.so /usr/lib/libhidapi-hidraw.so
sudo cp -f ykam24cmd/linux/libhidapi-hidraw.so /usr/lib/libhidapi-hidraw.so.0

sudo cp -f ykam24cmd/linux/libhidapi-libusb.so /usr/lib/libhidapi-libusb.so
sudo cp -f ykam24cmd/linux/libhidapi-libusb.so /usr/lib/libhidapi-libusb.so.0

