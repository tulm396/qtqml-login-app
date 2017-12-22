#include "fileio.h"

FileIO::FileIO()
{

}

bool FileIO::writeTokenToFile(const QString &fileName, const QString &data)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Truncate);
    file.write(data.toLocal8Bit());
    file.close();
    return true;
}

QString FileIO::readTokenFromFile(const QString &source)
{
    QFile file(source);
    file.open(QFile::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    return QString(data);
}
