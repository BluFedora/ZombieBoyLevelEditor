#ifndef ASSETIO_HPP
#define ASSETIO_HPP

#include <QJsonDocument>

namespace zombie_le
{
  class AssetIO
  {
    public:
      static QJsonDocument loadJson(const QString& path);

    private:
      AssetIO() = delete;
  };
}

#endif // ASSETIO_HPP
