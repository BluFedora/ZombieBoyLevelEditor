#ifndef CMDNEWGAMEOBJECT_HPP
#define CMDNEWGAMEOBJECT_HPP

#include <QJsonObject>
#include <QPixmap>
#include <QUndoStack>

class GameObject;
class QTreeWidget;
class QGraphicsScene;
class SpriteSet;

enum CommandType
{
  CMD_NEWGAMEOBJECT = 0,
  CMD_LOADGAMEOBJECT = 1
};

class CmdNewGameObject : public QUndoCommand
{
  private:
    GameObject*       m_NewGameObject;
    QTreeWidget*      m_List;
    QGraphicsScene*   m_GfxScene;
    const SpriteSet*  m_SpriteSet;
    QPointF           m_SpawnLoc;
    bool              m_HappenedOnce;

  public:
    CmdNewGameObject(const SpriteSet* texture, QTreeWidget* list, QGraphicsScene* scene, const QPointF& spawnPoint);

  public:
    GameObject* gameobject() const { return this->m_NewGameObject; }

    void undo() override;
    void redo() override;
    int id() const override;
};

class CmdLoadGameObject : public QUndoCommand
{
  private:
    GameObject*       m_GameObject;
    QJsonObject       m_JsonData;
    QTreeWidget*      m_List;
    QGraphicsScene*   m_GfxScene;

  public:
    CmdLoadGameObject();

  public:
    void undo() override
    {
    }

    void redo() override
    {
    }

    int id() const override
    {
      return CMD_LOADGAMEOBJECT;
    }
};

#endif // CMDNEWGAMEOBJECT_HPP
