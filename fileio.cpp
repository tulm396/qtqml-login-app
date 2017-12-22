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

    if (!file.open(QFile::ReadOnly)) {
        return "";
    }

    QByteArray data = file.readAll();
    file.close();
    return QString(data);
}
