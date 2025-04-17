#include "CelestiaCore.h"
#include "pch.h"

int main(int argc, char *argv[]) {

  std::cout << "CelestiaCore is starting..." << std::endl;

  Celestia::CelestiaCore celestiaCore;
  celestiaCore.run();

  return 0;
}
