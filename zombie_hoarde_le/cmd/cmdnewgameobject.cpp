#include "cmdnewgameobject.hpp"

#include <QGraphicsScene>
#include <gameobject.hpp>
#include <spritesetlist.h>

CmdNewGameObject::CmdNewGameObject(const SpriteSet* texture, QTreeWidget* list, QGraphicsScene* scene, const QPointF& spawnPoint) :
  QUndoCommand("Command: New GameObject"),
  m_NewGameObject(nullptr),
  m_List(list),
  m_GfxScene(scene),
  m_SpriteSet(texture),
  m_SpawnLoc(spawnPoint),
  m_HappenedOnce(true)
{
}

void CmdNewGameObject::undo()
{
  this->m_SpawnLoc = this->m_NewGameObject->pos();
  this->m_GfxScene->removeItem(this->m_NewGameObject);

  delete this->m_List->takeTopLevelItem(
    this->m_List->indexOfTopLevelItem(this->m_NewGameObject)
  );
}

void CmdNewGameObject::redo()
{
  this->m_NewGameObject = new GameObject(QPixmap());

  this->m_NewGameObject->setPos(this->m_SpawnLoc.x(), this->m_SpawnLoc.y());

  if (this->m_SpriteSet) {
    m_NewGameObject->applySpriteSet(*this->m_SpriteSet, m_HappenedOnce);
    m_HappenedOnce = false;
  }

  this->m_GfxScene->addItem(this->m_NewGameObject);
  this->m_List->addTopLevelItem(this->m_NewGameObject);
}

int CmdNewGameObject::id() const
{
  return CMD_NEWGAMEOBJECT;
}
