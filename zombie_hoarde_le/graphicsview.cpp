#include "graphicsview.h"

#include <QDebug>
#include <QGLWidget>
#include <QKeyEvent>
#include <QMenu>

GraphicsView::GraphicsView(QWidget *parent) :
  QGraphicsView(parent)
{
  // this->setContextMenuPolicy(Qt::DefaultContextMenu);

  setViewport(new QGLWidget());
  setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  setResizeAnchor(AnchorViewCenter);
  setInteractive(true);
  setTransformationAnchor(AnchorUnderMouse);
  setDragMode(QGraphicsView::RubberBandDrag);
  //setCacheMode(QGraphicsView::CacheBackground);
  setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
  setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
}

void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu("Creation Menu", this);

  menu.addAction("New GameObject", [this]()
  {
    emit doAddGameObject(QPixmap());
  });

  menu.addAction("Attach RigidBody", [this]()
  {
    emit doAttachRigidBody();
  });

  menu.addAction("Export GameObject(s) To Json", []()
  {
    qDebug() << "TODO: Export J GameObject[s]";
  });

  menu.addAction("Export GameObject(s) To Code", []()
  {
    qDebug() << "TODO: Export C GameObject[s]";
  });

  menu.addAction("Remove RigidBody", [this]()
  {
    emit doRemoveRigidBody();
  });

  menu.addAction("Delete GameObject(s)", [this]()
  {
    emit doDeleteGameObjects();
  });

  menu.exec(this->mapToGlobal(event->pos()));
  event->accept();
}

#define SCALE_FACTOR 1.1

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
  if (event->modifiers() == Qt::ControlModifier)
  {
    if (event->key() == Qt::Key_Equal)
    {
      scale(SCALE_FACTOR, SCALE_FACTOR);
    }
    else if (event->key() == Qt::Key_Minus)
    {
      scale(1.0 / SCALE_FACTOR, 1.0 / SCALE_FACTOR);
    }
    else if (event->key() == Qt::Key_0)
    {
      this->resetTransform();
      this->centerOn(0.0, 0.0);
    }
  }

  if (event->key() == Qt::Key_Space)
  {
    setDragMode(QGraphicsView::ScrollHandDrag);
  }

  QGraphicsView::keyPressEvent(event);
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Space)
  {
    setDragMode(QGraphicsView::RubberBandDrag);
  }

  QGraphicsView::keyReleaseEvent(event);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
  // Note this doesn't handle event->pixelData() correctly yet
  // so it won't work nicely with multitouch trackpads.
  if (event->delta() > 0)
    scale(SCALE_FACTOR, SCALE_FACTOR);
  else
    scale(1.0 / SCALE_FACTOR, 1.0 / SCALE_FACTOR);

  event->accept();
}
