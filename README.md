# Chatter-Box
A simple chat application that can double up to host a chat server or a chat client, focused on providing more privacy to users

## Prerequisites for building

* The project uses qt library. Thus, qt developer headers must be installed to build the project.

#### Developer packages necessary in Debian Buster
```
qt5-default
qtbase5-dev
libqt5websockets-dev
```

## Build Instructions

```bash
qmake
make
```

The intermediate object files and other files will be written to the build directory.
The final executable will be placed in the project root directory.
