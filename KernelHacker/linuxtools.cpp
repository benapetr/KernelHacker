#include "linuxtools.hpp"

QString LinuxTools::exec(const char *cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    QString result = "";
    while(!feof(pipe))
    {
        if(fgets(buffer, 128, pipe) != NULL)
            result += QString(buffer);
    }
    pclose(pipe);
    return result;
}

