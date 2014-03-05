//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef KERNELPARAMETER_HPP
#define KERNELPARAMETER_HPP

#include <QFile>
#include <QList>
#include <QDir>
#include <QString>
#include "terminal.hpp"

class KernelParameter
{
    public:
        static void Init();
        static void RecursivelyFetch(QString path);
        static unsigned int Items;
        static unsigned int ItemsC;
        static QList<KernelParameter*> Parameters;
        KernelParameter(QString name, QString path);
        void Retrieve();
        QString Name;
        QString Value;
        QString Path;
        bool IsModifiable_Online;
        bool IsModifiable_Offline;
};

#endif // KERNELPARAMETER_HPP
