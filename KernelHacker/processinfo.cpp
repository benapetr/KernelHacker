//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "processinfo.hpp"

QList<ProcessInfo> ProcessInfo::ProcessList;

void ProcessInfo::Reload()
{
    ProcessList.clear();
    QDir *list = new QDir("/proc");
    if (!list->exists())
    {
        delete list;
        return;
    }
    QList<QFileInfo> info = list->entryInfoList();
    int x = 0;
    while (x < info.count())
    {
        QFileInfo i = info.at(x);
        if (i.isDir() && IsPID(i.fileName()))
        {
            ProcessInfo process;
            process.PID = i.fileName().toInt();
            process.Name = ReadAttr(i.fileName(), "comm");
            QStringList prop(ReadAttr(i.fileName(), "stat").split(' '));
            QStringList m(ReadAttr(i.fileName(), "statm").split(' '));
            process.VmSize = (unsigned long)SystemInfo::Pagesize * (unsigned long)m.at(0).toLong();
            if (m.count() > 1)
            {
                process.VmRss = (unsigned long)SystemInfo::Pagesize * (unsigned long)m.at(1).toLong();
            } else
            {
                process.nice = 0;
            }
            process.nice = prop.at(18).toInt();
            process.StartTime = prop.at(21).toLong();
            process.Oom = ReadAttr(i.fileName(), "oom_score").toInt();
            ProcessList.append(process);
        }
        x++;
    }
    delete list;
}

QString ProcessInfo::ReadAttr(QString pid, QString what)
{
    QFile file("/proc/" + pid + "/" + what);
    if (!file.open(QIODevice::ReadOnly))
    {
        return "<unknown>";
    }
    QString value = file.readAll();
    if (value.endsWith("\n"))
    {
        value = value.mid(0, value.length() - 1);
    }
    file.close();
    return value;
}

bool ProcessInfo::IsPID(QString name)
{
    bool ok;
    name.toInt(&ok);
    return ok;
}

ProcessInfo::ProcessInfo()
{
    this->PID = 0;
    this->Name = "";
    this->VmRss = 0;
    this->nice = 0;
    this->Swappiness = 0;
    this->Oom = 0;
    this->VmSize = 0;
}
