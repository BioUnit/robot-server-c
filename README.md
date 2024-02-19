# robot-server-c overview
This program controls Banana Pi M2 Zero GPIO over TCP connection from "robot-server-gui" app 
C language version

# Dependencies
- apt install build-essentials
- apt install libwebsockets-dev

# how to build
gcc main.c mygpio.c -lgpiod

# how to run
sudo ./a.out
