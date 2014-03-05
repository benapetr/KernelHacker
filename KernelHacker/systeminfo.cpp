#include "systeminfo.hpp"

int SystemInfo::Pagesize = 4096;

void SystemInfo::Init()
{
    Pagesize = LinuxTools::exec("getconf PAGESIZE").toInt();
}

SystemInfo::SystemInfo()
{
}
