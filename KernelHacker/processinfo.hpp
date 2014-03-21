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

//! This class itself represent a process in the system
//! it also contains a static list of all processes
class ProcessInfo
{
    public:
        static void Reload();
        static QString ReadAttr(QString pid, QString what);
        static QList<ProcessInfo> ProcessList;
        static bool IsPID(QString name);

        ProcessInfo();
        //! Process ID
        int PID;
        //! Name of process (this is root name, not full path)
        QString Name;
        //! Virtual memory size
        unsigned long VmSize;
        //! Resident memory size
        unsigned long VmRss;
        int Priority;
        int KernelNice;
        int Oom;
        int Swappiness;
        long StartTime;

};

#endif // PROCESSINFO_HPP
