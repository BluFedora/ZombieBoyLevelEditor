#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

  private:
    QPoint m_OldPos;

  public:
    GraphicsView(QWidget* parent = nullptr);

  protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

  signals:
    void doAddGameObject(const QPixmap& texture);
    void doAttachRigidBody(void);
    void doDeleteGameObjects(void);
    void doRemoveRigidBody(void);

};

#endif // GRAPHICSVIEW_H
