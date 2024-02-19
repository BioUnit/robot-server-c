# robot-server-c overview
This program controls Banana Pi M2 Zero GPIO over TCP connection from "robot-control-gui" app 
C language version

# How to use
- clone repo
- compile
- run "robot-server-c"
- change IP address in "robot-control-gui" sources (see README at "robot-control-gui")
- run "robot-control-gui"
- press buttons on gui

# Dependencies
- apt install libgpiod-dev
- apt install build-essentials
- apt install libwebsockets-dev

# how to compile
gcc main.c mygpio.c -lgpiod

# how to run
sudo ./a.out
