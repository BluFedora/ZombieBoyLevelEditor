#include "assetio.hpp"
#include "spritesetlist.h"

#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>
#include <QMimeType>
#include <QTextStream>

#include <QDebug>

SpriteSetList::SpriteSetList(QWidget *parent) :
  QListWidget(parent),
  m_SpriteSets(),
  m_JsonCache()
{
}

bool SpriteSetList::has_sprite_set(const QString& key) const
{
  return this->m_SpriteSets.contains(key);
}

const SpriteSet &SpriteSetList::sprite_set(const QString &key)
{
  return *this->m_SpriteSets.find(key);
}

void SpriteSetList::clearLoad()
{
  while (this->m_JsonCache.size() > 0)
    this->m_JsonCache.pop_back();
  this->m_SpriteSets.clear();
  this->clear();
}

void SpriteSetList::fromJson(const QJsonArray& jArray)
{
  QDir work_dir(QDir::currentPath());

  for (const auto& filename : jArray)
  {
    if (filename.isString())
    {
      qDebug() << "Try to load SpriteSet: " << (work_dir.absolutePath() + "/" + filename.toString());
      this->loadSet((work_dir.absolutePath() + "/" + filename.toString()));
    }
  }
}

QJsonArray SpriteSetList::toJson() const
{
  return this->m_JsonCache;
}

void SpriteSetList::loadSet(const QString& path)
{
  QMimeDatabase mimeDataBase;

  QMimeType mimeT = mimeDataBase.mimeTypeForFile(path);

  const auto fileType = mimeT.name();

  if (fileType == "application/json" ||
      fileType == "application/octet-stream" ||
      true)
  {
    QJsonDocument doc = zombie_le::AssetIO::loadJson(path);
    QJsonObject obj = doc.object();
    auto maybeName = obj.value("name");

    if (maybeName.isString())
    {
      const auto name = maybeName.toString();

      if (this->m_SpriteSets.contains(name))
      {
        QMessageBox::information(this,
                                 tr("What are you Doing?"),
                                 tr("That SpriteSet is Already Loaded!"));
      }
      else
      {
        QDir work_dir(QDir::currentPath());
        SpriteSet spriteSet;
        spriteSet.fromJson(obj);
        this->m_SpriteSets.insert(name, spriteSet);
        this->m_JsonCache.push_back(work_dir.relativeFilePath(path));
        QListWidgetItem* item = new QListWidgetItem(QIcon(spriteSet.texture.scaled(QSize(24, 24))), name);
        item->setToolTip("<html><img src=" + spriteSet.path + "/></html>");
        this->addItem(item);
      }
    }
    else
      QMessageBox::information(this,
                               tr("Invalid Sprite Set Json File"),
                               tr("That json file does not seem to be valid!"));
  }
  else
  {
    QMessageBox::information(this,
                             tr("What are you Doing?"),
                             ("That isn't even a JSon File!: " + fileType));
  }
}

void SpriteSetList::dragEnterEvent(QDragEnterEvent *event)
{
  event->accept();
}

void SpriteSetList::dragMoveEvent(QDragMoveEvent *event)
{
  event->accept();
}

void SpriteSetList::dragLeaveEvent(QDragLeaveEvent *event)
{
  event->accept();
}

void SpriteSetList::dropEvent(QDropEvent *event)
{
  const QMimeData* mimeData = event->mimeData();

  if (mimeData->hasUrls())
  {
    for (const auto& url : mimeData->urls())
    {
      this->loadSet(url.toLocalFile());
    }
  }
}


void AnimFrame::fromJson(const QJsonObject &jObject)
{
  this->frameIndex = jObject["frameIndex"].toInt();
  this->frameTime = jObject["frameIndex"].toDouble();
}

void Animation::fromJson(const QJsonArray &jArray)
{
  for (const auto& i : jArray)
  {
    AnimFrame obj;
    obj.fromJson(i.toObject());
    this->frames.push_back(obj);
  }
}

AnimationSet::AnimationSet()
{
}

void AnimationSet::fromJson(const QJsonArray &jArray)
{
  for (const auto& i : jArray)
  {
    Animation anim;
    anim.fromJson(i.toArray());
    this->animations.push_back(anim);
  }
}

SpriteSet::SpriteSet()
{
}

void SpriteSet::fromJson(const QJsonObject &jObject)
{
  this->animation.fromJson(jObject["animation"].toArray());
  qDebug() << "Attempt to load texture: " << jObject["texture"].toString();
  this->texture.load(jObject["texture"].toString());
  this->path = jObject["texture"].toString();
  this->name = jObject["name"].toString();
  this->numCols = jObject["numCols"].toInt();
  this->numRows = jObject["numRows"].toInt();
}
