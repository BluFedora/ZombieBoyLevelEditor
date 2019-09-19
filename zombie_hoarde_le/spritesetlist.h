#ifndef SPRITESETLIST_H
#define SPRITESETLIST_H

#include <QJsonArray>
#include <QListWidget>

class AnimFrame
{
public:
  int   frameIndex;
  float frameTime;

  void fromJson(const QJsonObject &jObject);

};

class Animation
{
public:
  QVector<AnimFrame> frames;

  void fromJson(const QJsonArray &jArray);

};

class AnimationSet
{
public:
  QVector<Animation> animations;

public:
  AnimationSet();

  void fromJson(const QJsonArray &jArray);

};

class SpriteSet
{
public:
  AnimationSet  animation;
  QPixmap       texture;
  QString       path;
  QString       name;
  int           numCols;
  int           numRows;

public:
  SpriteSet();

  void fromJson(const QJsonObject &jObject);
};

class SpriteSetList : public QListWidget
{
private:
  QMap<QString, SpriteSet> m_SpriteSets;
  QJsonArray m_JsonCache;

public:
  SpriteSetList(QWidget* parent = nullptr);

  bool              has_sprite_set(const QString& key) const;
  const SpriteSet&  sprite_set(const QString& key);


  void       clearLoad(void);
  void       fromJson(const QJsonArray& jArray);
  QJsonArray toJson(void) const;

protected:
  void loadSet(const QString& path);

  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dragLeaveEvent(QDragLeaveEvent *event) override;
  void dropEvent(QDropEvent *event) override;

};

#endif // SPRITESETLIST_H
