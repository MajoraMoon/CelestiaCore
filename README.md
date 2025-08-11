# CelestiaCore - Build Instructions

## Requirements

- **CMake** (version 3.15 or higher)
- **A compiler** (e.g. `gcc`)
- **Make** or **Ninja**


### Notes

All required libraries are included in the `lib/` folder.  
No external dependencies are needed, they will be compiled together with the project.  
I prefer this approach because external dependencies can sometimes be a pain to manage on certain distributions or operating systems.

The build has been tested on:
- **Linux** (Arch-based) using `gcc` / `g++`
- **Windows** with MinGW & MSYS2

#### MSYS2 Requirements
Speaking of no external dependencies... If compiling with **MSYS2**, these packages are probably needed.  
Without them, the compiler may try to build a Linux (X11/Wayland) version instead of a Windows one:

```sh
pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
```

Not the biggest fan of Windows
## Steps

1. **Clone the repository:**

   ```bash
   git clone https://github.com/MajoraMoon/CelestiaCore.git
   cd CelestiaCore
   ```

2. **Create a build folder:**

   ```bash
   mkdir build
   cd build
   ```


3. **Configure the Project with CMake**
By default, the build type is `RelWithDebInfo`. Run:

   ```bash
   cmake ..
   ```

   **Optional build types:**

   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Debug       # For debugging
   cmake .. -DCMAKE_BUILD_TYPE=Release     # For optimized release builds
   cmake .. -DCMAKE_BUILD_TYPE=MinSizeRel  # For smaller binaries with decent performance
   ```

   For more information, check out the [SDL3 CMake documentation](https://wiki.libsdl.org/SDL3/README/cmake).#



 4. **Build the Project**

      You can build the project using one of the following tools:

      ```bash
      make     
      ```

      **or**

      ```bash
      ninja       # If you have Ninja installed (usually faster)
      ```

      *For faster compilation (may stress your CPU):*

      ```bash
      cmake --build . --parallel
      ```


5. **Run the Executable**

   After building, run the program with:

   ```bash
   ../bin/CelestiaCore
   ```

---
 ## Directory Structure

```
CelestiaCore/
├── bin/                 # Executable output
├── build/               # Build folder
├── lib/                 # Libraries
├── src/                 # Source code
└── README.md            # This file
```
