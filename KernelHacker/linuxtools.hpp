//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef LINUXTOOLS_HPP
#define LINUXTOOLS_HPP

#include <QString>
#include <iostream>
#include <stdio.h>

namespace LinuxTools
{
    QString exec(const char* cmd);
}

#endif // LINUXTOOLS_HPP
