#ifndef FILEIO_H
#define FILEIO_H

#include <QFile>

class FileIO
{
public:
    FileIO();
    static bool writeTokenToFile(const QString& fileName, const QString& data);
    static QString readTokenFromFile(const QString& source);
};

#endif // FILEIO_H
