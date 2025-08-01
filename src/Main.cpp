// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
// clang-format on

/**
 *
 *
 * Note: Depending on the GPU, Desktop Enviroment, Window Manager and display
 * server protocol the perfomance will vary like in every other graphical
 * application.
 *
 * Nvidia GPU's on Linux are always a pain. Proprietary Nvidia Drivers are
 * poorly working on Wayland. AMD GPU'S will work better, they actually respect
 * some kind of open source nature.
 *
 * OpenGL is not developed anymore but it will still gonna supported for a long
 * time.
 *
 * I compiled this project on Windows 10/11 with MingW and MSYS2 and on Linux on
 * the KDE Plasma 6 enviroment on EndeavourOS.
 */

int main(int argc, char *argv[]) {

  std::cout << "CelestiaCore is starting..." << std::endl;

  Celestia::CelestiaCore celestiaCore;
  celestiaCore.run();

  return 0;
}
