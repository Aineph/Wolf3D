# Wolf3D
A remake of the game Wolfenstein 3D using the ray-casting technique.

![Wolf3D Illustration](https://res.cloudinary.com/deexzd1vz/image/upload/v1689606081/wolf3d_wjhiou.png "Wolf3D Illustration")

# Summary

* Build System
* User Manual
* Specifications

# Build System

This project uses the SFML Library.
Before you install this repository, please make sure the library is installed on your file system.
If you don't have it yet, you can get it by following this link: https://www.sfml-dev.org/download-fr.php.

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


Here is the list of the engine's controls:

- **Z**: Move forward.
- **S**: Move backward.
- **Q**: Move left.
- **D**: Move right.
- **Up arrow**: Camera up.
- **Down arrow**: Camera down.
- **Left arrow**: Camera left.
- **Right arrow**: Camera right.
- **T**: Toggles the rendering mode, either textured or vanilla.
- **Escape**: Quits the program.

# Specifications

The Wolf3D project uses the ray-casting algorithm to render a 2D map to a semi-3D environment.
This section will be completed in a future release.
