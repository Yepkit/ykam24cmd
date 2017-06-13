# YKAM24CMD Command Application


Control application for Yepkit YKAMELEAN24 board.


Description
===========

Console application developed to illustrate the programmatic control of YKAMELEAN24 capabilities.
It executes one command per run, being appropriate to be executed as a console command.
But it can be easily adapted to execute a work-flow with multiple commands and we encourage you to alter it to best fit your needs.

The implementation makes use of hidapi open-source library which is portable across several operating systems.
We include a Visual Studio solution file for building on Windows. For Linux we include a build and installation script, `build.sh` and `install.sh` respectively, for building and installing the application. 

Note that hidapi is not included in the source code package and has to be obtained beforehand. For Linux, if the
`build.sh` script is used, to build the application, it will take care of downloading and building the hidapi library for you. In Windows this step has to
be manually performed by the user.


Licensing
=========

The source code is licensed under the Apache License, Version 2.0. 
Refer to [LICENSE](LICENSE.md) file.


Building
========

The steps for building on Windows and Linux are detailed bellow.

Windows
-------

The instructions bellow assume MinGW has been installed in your system.

Before building the application from source on Windows you need to get the [hidapi library](http://www.signal11.us/oss/hidapi/) and build it.
Follow the instructions in the hidapi documentation for building the library in the several systems. 

After building the hidapi library you need to include the relevant hidapi files to *ykam24cmd* project. 

Copy to `src\windows\` the following hidapi library files:
- hidapi.h
- hidapi.dll
- hidapi.exp
- hidapi.lib


Now to build open the command line terminal (cmd), navigate to the ykam24cmd project root folder and run the following command.
```
make -f Makefile_win
```
At this point the `ykam24cmd.exe` executable has been created in the `bin\` folder.


The next step is to make the dynamically linked library accessible to executable.
We can install the `hidapi.dll` in the system or ensure that a copy of the file is in the same folder than the `ykam24cmd.exe`.


Linux
-----

The easiest way to build the application on Linux is to use the `build.sh` script which is in the ykam24cmd project root folder.
Nonetheless the application can be built running make and using the provided Makefile directly, but it will require
some prior manual configuration detailed ahead. 

To build the application using the scripts run the following inside the project root folder.
```
./build.sh
```
Note that the script requires Internet connectivity to fetch the latest version of hidapi library.

Some dependencies may not have been satisfied and some additional systems components and utilities may be required.
If that was the case please install them and re-run the script. 

After a successful build process you can install the ykam24cmd command in the system. To do so, in project root folder run:
```
sudo ./install.sh
```

After install, the `ykam24cmd` command is ready for use.


On the other hand, if you want to build running make directly with the provided Makefile do the following.

First get the [hidapi library](http://www.signal11.us/oss/hidapi/) and build it.
Please follow the instructions in the hidapi documentation for building the library in the several systems. 

After building the hidapi library include the relevant hidapi files to *ykam24cmd* project. 

Copy to `linux/` the `libhidapi-hidraw.so` and the `libhidapi-libusb.so` files from hidapi library you
just built.

Now add the following lines to the `platformdefs.h` file which is in the project root folder.
```
#ifndef PLATFORMDEFS_H
#define PLATFORMDEFS_H
#define LINUX
#endif
```


Next, in the project root folder run `make` to build the application.
If the build process is successful the ykam24cmd executable will be created in the `bin/` folder.

The next step is to make the shared library accessible to the executable.
Do this by installing the *libhidapi-hidraw.so* or the *libhidapi-libusb.so*, depending if the hidraw or the libusb back-end is to be used (in doubt install both), in a system folder (e.g., /usr/lib/) or set the environment variable *LD_LIBRARY_PATH* with the path to the library files. 
Alternatively you can run the script `install.sh` which is located in the project root folder.


Using it
========

Windows
-------
Navigate to the `bin\` folder and run `ykam24cmd.exe` to print available command options.


Linux
-----
For Linux the command options and syntax are the same with the slight difference that the executable file does not have the `.exe` extension.
Also depending of your user permissions you may need to precede the command with the *sudo* directive.


For more information and resources for the YKAMELEAN24 board please visit the [yepkit website YKAMELEAN24 page](https://www.yepkit.com/product/300105/YKAMELEAN24).









