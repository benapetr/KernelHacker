#ifndef KERNELPARAMETER_HPP
#define KERNELPARAMETER_HPP

#include <QFile>
#include <QList>
#include <QDir>
#include <QString>

class KernelParameter
{
    public:
        static void Init();
        static void RecursivelyFetch(QString path);
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
