#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <fstream>

#include "LinkStorage.h"
#include "ChatBox.h"
#include "User.h"
#include "UserStorage.h"
#include "Shell.h"
#include "SHA1.h"

#if defined(_WIN32) 
#define PLATFORM_NAME "windows 32-bit" // Windows 32-bit
#elif defined(_WIN64)
#define PLATFORM_NAME "windows 64-bit" // Windows 64-bit
#elif defined(__linux__)
#define PLATFORM_NAME "linux"     // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos и другие
#include <sys/utsname.h>          // Для uname()
#else
#define PLATFORM_NAME  "OS not detected" // ОС не распознана
#endif


int main()
{
#if defined(__linux__)
    struct utsname utsname; // объект для структуры типа utsname

    uname(&utsname); // передаем объект по ссылке

    // распечатаем на экране информацию об операционной системе
    std::cout << PLATFORM_NAME << std::endl;
    std::cout << "OS name: " << utsname.sysname << std::endl;
    std::cout << "Host name: " << utsname.nodename << std::endl;
    std::cout << "OS release: " << utsname.release << std::endl;
    std::cout << "OS version: " << utsname.version << std::endl;
    std::cout << "Machine name: " << utsname.machine << std::endl;
#elif (defined(_WIN32) || defined(_WIN64))
    std::cout << PLATFORM_NAME << std::endl;
#else
    std::cout << PLATFORM_NAME << std::endl;
#endif

    

    std::cout << "Programm start\n";
    Shell sh;
    sh.work();
    std::cout << "Programm end\n";

    return 0;
}
