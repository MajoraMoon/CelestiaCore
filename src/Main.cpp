#include "pch.h"
#include "CelestiaCore.h"

/**
 *
 * Note: If you compile this program running natively under wayland, the perfomance might be worse than over x11 or
 * xWayland. I could not find out the reason for it, I assume it is my use of an nvidia graphics card (proprietary
 * drivers) in combination with OpenGL. SDL3 could be a factor too. The Operating System itself should not effect it
 * much. Linux can often bring better perfomance than windows (at least on x11) because it uses less ressources for
 * other processes
 *
 * I compiled this project on Windows 10/11 with MingW and MSYS2 and on Linux on the KDE Plasma 6 enviroment on
 * EndeavourOS
 *
 */

int main(int argc, char *argv[])
{

    std::cout << "CelestiaCore is starting..." << std::endl;

    Celestia::CelestiaCore celestiaCore;
    celestiaCore.run();

    return 0;
}
