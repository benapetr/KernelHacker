//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef PROCESSINFO_HPP
#define PROCESSINFO_HPP

#include <QList>
#include <QDir>
#include <QFile>
#include <QString>
#include "systeminfo.hpp"

class ProcessInfo
{
    public:
        static void Reload();
        static QString ReadAttr(QString pid, QString what);
        static QList<ProcessInfo> ProcessList;
        static bool IsPID(QString name);
        ProcessInfo();
        int PID;
        QString Name;
        unsigned long VmSize;
        unsigned long VmRss;
        int nice;
        long StartTime;

};

#endif // PROCESSINFO_HPP
