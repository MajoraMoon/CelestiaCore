# CelestiaCore - Build Instructions

## Requirements

- **CMake** (version 3.15 or higher)
- **A compiler** (e.g. `gcc`)
- **Make** or **Ninja**

### Notes:
All required libraries are included in the `lib/` folder. No external dependencies are needed as they will be compiled with the project. I don't really like external dependencies, sometimes they are a pain to manage on some distros or operating Systems.
(Tested the compilation on an arch based Linux distribution with gcc/g++ and on Windows with MingW & MSYS2 )

---

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
