//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "kernelparameter.hpp"

QList<KernelParameter*> KernelParameter::Parameters;
unsigned int KernelParameter::Items = 0;
unsigned int KernelParameter::ItemsC = 0;

void KernelParameter::Init()
{
    ItemsC = 0;
    Items = 0;
    RecursivelyFetch("/proc/sys");
}

void KernelParameter::RecursivelyFetch(QString path)
{
    QDir directory(path);
    if (!directory.exists())
    {
        return;
    }
    QList<QFileInfo> info = directory.entryInfoList();
    int x = 0;
    while (x < info.count())
    {
        QFileInfo i = info.at(x);
        if (i.isDir())
        {
            QString file_abs_path = i.absoluteFilePath();
            if (file_abs_path == path || file_abs_path.length() < path.length())
            {
                x++;
                continue;
            }
            RecursivelyFetch(file_abs_path);
        } else if (i.isFile())
        {
            QString tree = path;
            if (tree.startsWith("/proc/sys/"))
            {
                tree = tree.mid(10);
            }
            tree.replace("/", ".");
            Items++;
            ItemsC++;
            if (ItemsC > 100)
            {
                Terminal::Write("Retrieved " + QString::number(Items) + " kernel parameters so far");
                ItemsC = 0;
            }
            Parameters << new KernelParameter(tree + "." + i.fileName(), i.absoluteFilePath());
        }
        x++;
    }
}

KernelParameter::KernelParameter(QString name, QString path)
{
    this->Name = name;
    this->Path = path;
    this->IsModifiable_Offline = false;
    this->IsModifiable_Online = false;
    this->Value = "{unknown}";
    this->Retrieve();
}

void KernelParameter::Retrieve()
{
    QFile file(this->Path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    this->Value = QString(file.readAll());
    while (Value.contains("\n\n"))
    {
        Value.replace("\n\n", "\n");
    }
    if (Value.endsWith("\n"))
    {
        this->Value = Value.mid(0, Value.length() - 1);
    }
    this->IsModifiable_Online = file.isWritable();
    this->IsModifiable_Offline = file.isWritable();
    file.close();
}
