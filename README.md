# Wolf3D
A remake of the game Wolfenstein 3D using the ray-casting technique.

# Summary

* Build System
* User Manual
* Specifications

# Build System

This project uses the SFML Library.
Before you install this repository, please make sure the library is installed on your file system.

You will need CMake in order to compile. The minimum version required is 3.14.
You can download it there: https://cmake.org/download/.
If you can't get the latest version of CMake, you can still try to change the value in the CMakeLists.txt.
You will also need at least a C++ compiler to build the binary.

This section will guide you on how to build the target using cmake.
After cloning the repository, create an empty "build" repository inside this project, by using the command:

```
$> mkdir build
```

Once the repository is created run the following commands:

```
$> cd build/
# If you are using a linux system (including macOS)
$> cmake .. && make
# If you want to compile it on an other platform
$> cmake .. -G [platform_name]
# This command is an example of how to launch the program
$> ./Wolf3D
```

# User Manual

This section is not yet completed. It will be available in a future release.

# Specifications

This section is not yet completed. It will be available in a future release.
