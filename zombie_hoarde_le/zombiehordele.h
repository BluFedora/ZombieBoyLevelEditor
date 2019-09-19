#ifndef ZOMBIEHOADELE_H
#define ZOMBIEHOADELE_H

#include <QClipboard>
#include <QFileSystemModel>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMainWindow>
#include <QUndoStack>

#include "ui_zombiehordele.h"

namespace Ui {
class ZombieHordeLE;
}

class QListWidget;
class GameObject;
class SpriteSetList;

class ZombieHordeScene : public QGraphicsScene
{
    Q_OBJECT

  signals:
    void doAddGameObject(const QPixmap& texture);

  public:
    SpriteSetList*  m_SpriteSets;
    QTreeWidget*    m_GoList;
    QUndoStack      m_UndoStack;
    QClipboard*     m_Clippy;
    QPointF         m_LastMousePos;

  public:
    ZombieHordeScene(QObject* parent);

    GameObject* cmdAddGameObject(const SpriteSet* spriteset, const QPointF& spawnPoint);

    void       setSpriteSetList(SpriteSetList* list);
    void       clearAll(void);
    void       fromJson(const QJsonArray& json);
    QJsonArray toJson(void) const;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

  public slots:
    void attachRigidBody(void);
    void removeRigidBody(void);
    void deleteSelectedItems(void);

};

class ZombieHordeLE : public QMainWindow
{
    Q_OBJECT

private:
    ZombieHordeScene*   m_GfxScene;
    QFileSystemModel    m_FileSystemModel;
    QString             m_WorkDir;
    bool                m_LevelLoaded;

public:
    explicit ZombieHordeLE(QWidget *parent = 0);

    ~ZombieHordeLE();

private:
    void updateAssetsView(const QString &path);
    void onLoadLevel(const QString& filepath);

public slots:
    void onSetAssetPath(void);
    void onAddGameObject();
    void onDeleteGameObjects(void);
    void onSaveLevel(void);
    void onLoadLevel(void);


private:
    Ui::ZombieHordeLE *ui;

  protected:
    void closeEvent(QCloseEvent* event) override;

};

#endif // ZOMBIEHOADELE_H
