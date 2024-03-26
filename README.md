# robot-server-c overview
This program controls Banana Pi M2 Zero GPIO over TCP connection from "robot-control-gui" app and streams video from the camera
C language version

# How to use
- clone repo
- change IP address in "myvideo.c"
- compile
- run "robot-server-c"
- change IP address in "robot-control-gui" sources (see README at "robot-control-gui")
- run "robot-control-gui"
- press buttons on gui
- observe video from the camera

# Dependencies
- apt install libgpiod-dev
- apt install build-essentials
- apt install libwebsockets-dev
- Gstreamer package (use commands from here: https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c )

# How to compile
Add paths to GCC environment variable:
- export CPATH=/usr/include/gstreamer-1.0/:/usr/include/glib-2.0/:/usr/lib/arm-linux-gnueabihf/glib-2.0/include/
Compile:
- gcc -g main.c mygpio.c myvideo.c -lgstreamer-1.0 -lglib-2.0 -lgobject-2.0 -lgpiod

# How to run
sudo ./a.out

# Youtube tutorial commits bindings
To be able to see exact source code please use : 
- git checkout COMMIT_NUMBER_YOU_NEED

Youtube tutorials bindings:
- How to use GPIO in C and C++ applications on Banana Pi (Armbian) -> git checkout 620e84c3704600dc5b8176e9ec309ccb411e6f98
- How to TCP on Embedded Linux -> git checkout 620e84c3704600dc5b8176e9ec309ccb411e6f98
