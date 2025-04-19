# CelestiaCore - Build Instructions

## Requirements

- **CMake** (version 3.15 or higher)
- **A compiler** (e.g. `gcc`)
- **Make** or **Ninja**

### Notes:
All required libraries are included in the `lib/` folder. No external dependencies are needed as they will be compiled with the project. 
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

3. **Run CMake and append an optional build type for SDL3 (default is `RelWithDebInfo`):**

   ```bash
   cmake ..
   ```

   Optional alternatives:

   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Debug
   cmake .. -DCMAKE_BUILD_TYPE=Release
   cmake .. -DCMAKE_BUILD_TYPE=MinSizeRel
   ```

   For more information, refer to the [SDL3 CMake documentation](https://wiki.libsdl.org/SDL3/README/cmake).

4. **Build the project:**

   ```bash
   make
   ```
**Or**

   ```bash
   ninja
   ```

   Or, for faster compilation (Could slow down your computer):

   ```bash
   cmake --build . --parallel
   ```

5. **Run the executable:**

   ```bash
   ./bin/CelestiaCore
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
