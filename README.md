# CelestiaCore - Build Instructions

## Requirements

- **CMake** (version 3.15 or higher)
- **A compiler** (e.g. `gcc`)
- **Make** or **Ninja**

### Notes:
All required libraries are included in the `lib/` folder. No external dependencies are needed as they will be compiled with the project.

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

3. **Run CMake:**

   ```bash
   cmake ..
   ```

4. **Build the project** (choose one):

   - With **Make**:

     ```bash
     make
     ```

   - With **Ninja**:

     ```bash
     ninja
     ```

5. **Run the executable:**

   ```bash
   ./bin/CelestiaCore
   ```

## Directory Structure

```
CelestiaCore/
├── bin/                 # Executable output
├── build/               # Build folder
├── lib/                 # Libraries
├── src/                 # Source code
└── README.md            # This file
```
