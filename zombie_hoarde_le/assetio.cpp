#include "assetio.hpp"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

namespace zombie_le
{
  QJsonDocument AssetIO::loadJson(const QString& path)
  {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
    {
      QMessageBox::information(nullptr, "Unable to open file", file.errorString());
      return QJsonDocument();
    }

    QTextStream in(&file);
    QString jsonStr;

    while(!in.atEnd()) {
      jsonStr += in.readLine();
    }

    file.close();

    const std::string rawStr = jsonStr.toStdString();

    return QJsonDocument::fromJson(QByteArray::fromRawData(rawStr.c_str(), (int)rawStr.size()), nullptr);
  }
}
