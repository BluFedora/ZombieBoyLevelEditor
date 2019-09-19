#include "zombiehordele.h"
#include "ui_zombiehordele.h"

#include "assetio.hpp"
#include "gameobject.hpp"
#include "cmd/cmdnewgameobject.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMimeData>
#include <QMimeDatabase>
#include <QToolTip>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QClipboard>

#include <memory>
#include <float.h>

ZombieHordeLE::ZombieHordeLE(QWidget *parent) :
  QMainWindow(parent),
  m_GfxScene(new ZombieHordeScene(this)),
  m_FileSystemModel(this),
  m_WorkDir(),
  m_LevelLoaded(false),
  ui(new Ui::ZombieHordeLE)
{
  ui->setupUi(this);

  this->m_GfxScene->m_GoList = this->ui->gameObjectList;

  this->ui->gameObjectList->invisibleRootItem()->setFlags(
        this->ui->gameObjectList->invisibleRootItem()->flags() | Qt::ItemIsDropEnabled
        );

  this->ui->treeView->setModel(&this->m_FileSystemModel);
  this->ui->treeView->hideColumn(1); // Size
  this->ui->treeView->hideColumn(2); // Type
  this->ui->treeView->hideColumn(3); // Date Modified
  this->ui->treeView->setDragEnabled(true);
  this->ui->treeView->setAcceptDrops(true);
  this->ui->treeView->viewport()->setAcceptDrops(true);
  this->ui->treeView->setDropIndicatorShown(true);
  this->ui->treeView->setDragDropMode(QAbstractItemView::InternalMove);
  this->updateAssetsView(QCoreApplication::applicationDirPath() + "/../assets/");

  connect(this->ui->treeView, &QTreeView::doubleClicked, [this](const QModelIndex &index)
  {
    const auto path = this->m_FileSystemModel.filePath(index);

    if (!this->m_FileSystemModel.isDir(index) && QFileInfo(path).suffix() == "json")
    {
      if (QMessageBox::question(this,
                                "Would you like to Save the Current Level?",
                                "Would you like to Save the Current Level?",
                                QMessageBox::No,
                                QMessageBox::Save) == QMessageBox::Save)
      {
        this->onSaveLevel();
      }
      this->onLoadLevel(path);
    }
  });

  connect(this->ui->graphicsView, &GraphicsView::doAddGameObject,     this,             &ZombieHordeLE::onAddGameObject);
  connect(this->ui->graphicsView, &GraphicsView::doAttachRigidBody,   this->m_GfxScene, &ZombieHordeScene::attachRigidBody);
  connect(this->ui->graphicsView, &GraphicsView::doRemoveRigidBody,   this->m_GfxScene, &ZombieHordeScene::removeRigidBody);
  connect(this->ui->graphicsView, &GraphicsView::doDeleteGameObjects, this,             &ZombieHordeLE::onDeleteGameObjects);
  connect(this->m_GfxScene,       &ZombieHordeScene::doAddGameObject, this,             &ZombieHordeLE::onAddGameObject);

  connect(this->ui->gameObjectList, &QTreeWidget::itemClicked, [this](QTreeWidgetItem *item)
  {
    if (item && item->type() == Qt::UserRole + 1)
    {
      auto itemt = (GameObject *)item;
      itemt->setSelected(true);
    }
  });

  connect(this->ui->gameObjectList, &QTreeWidget::itemDoubleClicked, [this](QTreeWidgetItem *item, int column)
  {
    if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier)
    {
      if (item->parent() == nullptr) {
        this->ui->graphicsView->centerOn((GameObject*)item);
        this->ui->gameObjectList->clearSelection();
      }
    }
    else
    {
      if (item->parent() == nullptr && column == 0)
      {
        this->ui->gameObjectList->editItem(item, column);
      }
      else if (item->parent() != nullptr && column == 1)
      {
        this->ui->gameObjectList->editItem(item, column);
      }
    }
  });

  connect(this->ui->gameObjectList, &QTreeWidget::itemSelectionChanged, [this]()
  {
    for (int i = 0; i < this->ui->gameObjectList->topLevelItemCount(); ++i)
    {
      auto itemt = (GameObject *)this->ui->gameObjectList->topLevelItem(i);
      itemt->setSelected(itemt->QTreeWidgetItem::isSelected());
    }
  });

  this->m_GfxScene->setSpriteSetList(this->ui->listWidget_2);
  this->ui->graphicsView->setAcceptDrops(true);
  this->ui->graphicsView->setScene(this->m_GfxScene);
  this->m_GfxScene->addText("(0, 0)");

  //this->ui->dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  //this->ui->dockWidget_2->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  //this->ui->treeViewDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

  this->ui->undoViewList->setStack(&this->m_GfxScene->m_UndoStack);

  auto viewMenu = this->ui->menuBar->addMenu("View");
  viewMenu->addAction(this->ui->treeViewDock->toggleViewAction());
  viewMenu->addAction(this->ui->dockWidget->toggleViewAction());
  viewMenu->addAction(this->ui->dockWidget_2->toggleViewAction());
  viewMenu->addAction(this->ui->undoViewDock->toggleViewAction());
}

ZombieHordeLE::~ZombieHordeLE()
{
  delete this->m_GfxScene;
  delete ui;
}

void ZombieHordeLE::updateAssetsView(const QString& path)
{
  if (!QDir::setCurrent(path + "/../")) {
    qDebug() << "Could not set the WorkDir to: " << path + "/../";
  } else {
    qDebug() << "Working Directory is now: " << QDir::currentPath();
  }
  this->m_WorkDir = path;
  this->ui->treeView->setRootIndex(this->m_FileSystemModel.setRootPath(path));
}

void ZombieHordeLE::onLoadLevel(const QString &filepath)
{
  m_LevelLoaded = true;

  this->ui->listWidget_2->clearLoad();

  QJsonDocument doc = zombie_le::AssetIO::loadJson(filepath);

  QJsonObject obj = doc.object();
  this->ui->listWidget_2->fromJson(obj.value("sprite_sets").toArray());
  this->m_GfxScene->clearAll();
  this->m_GfxScene->addText("(0, 0)");
  this->m_GfxScene->fromJson(obj.value("gameobjects").toArray());
}

void ZombieHordeLE::onSetAssetPath()
{
  QString path = QFileDialog::getExistingDirectory(this, "Select The Assets Path", QString(), QFileDialog::ShowDirsOnly);

  if (path != "") {
    this->updateAssetsView(path);
  }
}

void ZombieHordeLE::onAddGameObject()
{
  this->m_GfxScene->cmdAddGameObject(nullptr, QPointF());
}

void ZombieHordeLE::onDeleteGameObjects()
{
  this->m_GfxScene->deleteSelectedItems();
}

void ZombieHordeLE::onSaveLevel()
{
  const QString filepath = QFileDialog::getSaveFileName(this, "Level File To Save", (QDir::currentPath() + "/assets/levels/"), "Json (*.json)");

  if (!filepath.isEmpty())
  {
    QJsonObject level_data;

    level_data["sprite_sets"] = this->ui->listWidget_2->toJson();
    level_data["gameobjects"] = this->m_GfxScene->toJson();

    QFile file(filepath);

    if (!file.open(QIODevice::WriteOnly))
    {
      QMessageBox::information(this, tr("Unable to open file"), file.errorString());
      return;
    }

    file.write(QJsonDocument(level_data).toJson(QJsonDocument::Indented));
  }
}

void ZombieHordeLE::onLoadLevel()
{
  const QString filepath = QFileDialog::getOpenFileName(this, "Level File To Load", "", "Json (*.json)");

  if (!filepath.isEmpty()) {
    this->onLoadLevel(filepath);
  }
}

void ZombieHordeLE::closeEvent(QCloseEvent* event)
{
  if (QMessageBox::question(this,
                            "Are You Sure you want to Exit?",
                            "Are You Sure you want to Exit?",
                            QMessageBox::No,
                            QMessageBox::Yes) == QMessageBox::Yes)
  {
    event->accept();
  }
  else
  {
    event->ignore();
  }
}

ZombieHordeScene::ZombieHordeScene(QObject* parent) :
  QGraphicsScene(parent),
  m_SpriteSets(nullptr),
  m_UndoStack(this),
  m_Clippy(QGuiApplication::clipboard())
{
}

GameObject* ZombieHordeScene::cmdAddGameObject(const SpriteSet* spriteset, const QPointF& spawnPoint)
{
  auto cmd = new CmdNewGameObject(spriteset, this->m_GoList, this, spawnPoint);
  this->m_UndoStack.push(cmd);
  return cmd->gameobject();
}

void ZombieHordeScene::setSpriteSetList(SpriteSetList* list)
{
  this->m_SpriteSets = list;
}

void ZombieHordeScene::clearAll()
{
  const auto item_list = this->items();

  for (auto& item : item_list)
  {
    this->removeItem(item);
    delete item;
  }
}

void ZombieHordeScene::fromJson(const QJsonArray &json)
{
  this->m_UndoStack.clear();

  for (const auto& jsonObj : json)
  {
    const auto objData = jsonObj.toObject();
    QString ss = objData.value("sprite").toObject().value("spriteSet").toString("__null");

    if (ss != "__null")
    {
      QPointF pos = {
        objData.value("sprite").toObject().value("positionX").toDouble(0.0),
        objData.value("sprite").toObject().value("positionY").toDouble(0.0)
      };
      auto go = this->cmdAddGameObject(&this->m_SpriteSets->sprite_set(ss), pos);
      go->fromJson(objData);
      go->updateTint();
    }
  }

  this->m_UndoStack.clear();
}

QJsonArray ZombieHordeScene::toJson() const
{
  QJsonArray ret;

  for (int i = 0; i < this->m_GoList->topLevelItemCount(); ++i)
  {
    GameObject* gameObject = (GameObject*)this->m_GoList->topLevelItem(i);
    QJsonObject go_j;
    gameObject->toJson(go_j);
    ret.push_back(go_j);
  }

  return ret;
}

void ZombieHordeScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsScene::mousePressEvent(event);
}

void ZombieHordeScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsScene::mouseMoveEvent(event);

  m_LastMousePos = event->scenePos();

  for (const auto& item : this->selectedItems())
  {
    QToolTip::showText(event->screenPos(),
                       QString("(x = ") +
                       QString::number(item->pos().x()) +
                       QString(", y = ") +
                       QString::number(item->pos().y()) +
                       QString(", width = ") +
                       QString::number(item->boundingRect().width()) +
                       QString(", height = ") +
                       QString::number(item->boundingRect().height()) +
                       QString(")"),
                       nullptr,
                       QRect());
    break;
  }
}

void ZombieHordeScene::keyPressEvent(QKeyEvent* event)
{
  if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
  {
    this->deleteSelectedItems();
  }
  else if ((event->modifiers() & Qt::CTRL) && event->key() == Qt::Key_C)
  {
    QJsonArray array;

    for (const auto& item : this->selectedItems())
    {
      QJsonObject ret;
      static_cast<GameObject*>(item)->toJson(ret);
      array.push_back(ret);
    }

    m_Clippy->setText(QString::fromStdString(QJsonDocument(array).toJson().toStdString()), QClipboard::Clipboard);
  }
  else if ((event->modifiers() & Qt::CTRL) && event->key() == Qt::Key_V)
  {
    if (m_Clippy->ownsClipboard())
    {
      const std::string rawStr = m_Clippy->text(QClipboard::Clipboard).toStdString();
      QJsonDocument data = QJsonDocument::fromJson(QByteArray::fromRawData(rawStr.c_str(), (int)rawStr.size()), nullptr);

      for (const auto& jsonObj : data.array())
      {
        const auto objData = jsonObj.toObject();
        QString ss = objData.value("sprite").toObject().value("spriteSet").toString("__null");

        if (ss != "__null")
        {
          QPointF pos = {
            m_LastMousePos
          };

          qDebug() << "mouse pos: " << m_LastMousePos;

          auto go = this->cmdAddGameObject(&this->m_SpriteSets->sprite_set(ss), pos);
          go->fromJson(objData);
          go->updateTint();

          go->setPos(m_LastMousePos.x(), m_LastMousePos.y());
        }
      }
    }
  }
  else
  {
    QGraphicsScene::keyPressEvent(event);
  }
}

void ZombieHordeScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
  if (event->source() == this->m_SpriteSets)
  {
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
      const auto fileNames = event->mimeData()->urls();

      qDebug() <<  fileNames;

      QMimeDatabase mimeDataBase;


      for (const auto& url : fileNames)
      {
        QMimeType mimeT = mimeDataBase.mimeTypeForFile(event->mimeData()->text());

        const auto fileType = mimeT.name();

        if (fileType == "image/png")
        {
          emit this->doAddGameObject(QPixmap(url.toLocalFile()));
        }
        else
        {
          qDebug() << "Invalid File Type";
        }

        qDebug() << fileType;
      }

      event->accept();
    }

    else if (mimeData->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
      QByteArray encoded = mimeData->data("application/x-qabstractitemmodeldatalist");
      QDataStream stream(&encoded, QIODevice::ReadOnly);

      while (!stream.atEnd())
      {
        int row, col;
        QMap<int,  QVariant> roleDataMap;

        stream >> row >> col >> roleDataMap;

        const auto gameobjects = this->items(event->scenePos());

        if (gameobjects.size() > 0)
        {
          for (const auto* go : gameobjects)
          {
            ((GameObject*)go)->applySpriteSet(this->m_SpriteSets->sprite_set(roleDataMap[Qt::DisplayRole].toString()));
          }
        }
        else
        {
          const auto spriteSetName = roleDataMap[Qt::DisplayRole].toString();
          auto gameobject = this->cmdAddGameObject(&this->m_SpriteSets->sprite_set(spriteSetName), event->scenePos());
          gameobject->setName(spriteSetName);
        }

        qDebug() << "Row: " << row << "Col: " << col << " roleDataMap: " << roleDataMap;
      }

      event->accept();
    }
    else
    {
      qDebug() << mimeData->formats();
    }
  }
}

void ZombieHordeScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
  if (event->source() == this->m_SpriteSets)
    event->accept();
  else
    QGraphicsScene::dragEnterEvent(event);
}

void ZombieHordeScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
  if (event->source() == this->m_SpriteSets)
    event->accept();
  else
    QGraphicsScene::dragMoveEvent(event);
}

void ZombieHordeScene::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
  if (event->source() == this->m_SpriteSets)
    event->accept();
  else
    QGraphicsScene::dragLeaveEvent(event);
}

void ZombieHordeScene::keyReleaseEvent(QKeyEvent* event)
{
  QGraphicsScene::keyReleaseEvent(event);
}

void ZombieHordeScene::attachRigidBody()
{
  QString filepath = QFileDialog::getOpenFileName(nullptr, QString("Select a RigidBody Json File"), QString(), QString("Json (*.json)"));

  if (!filepath.isEmpty())
  {
    QJsonDocument doc = zombie_le::AssetIO::loadJson(filepath);

    QJsonObject obj = doc.object();

    for (auto& item : selectedItems())
    {
      ((GameObject *)item)->applyRigidBody(obj);
    }
  }
}

void ZombieHordeScene::removeRigidBody()
{
  for (auto& item : selectedItems())
  {
    ((GameObject *)item)->applyRigidBody(nullptr);
  }
}

void ZombieHordeScene::deleteSelectedItems()
{
  while(!selectedItems().isEmpty())
  {
    auto item = selectedItems().front();
    removeItem(item);
    delete item;
  }
}
