#ifndef SYSTEMINFO_HPP
#define SYSTEMINFO_HPP

#include "linuxtools.hpp"

class SystemInfo
{
    public:
        static void Init();
        static int Pagesize;
        SystemInfo();
};

#endif // SYSTEMINFO_HPP
