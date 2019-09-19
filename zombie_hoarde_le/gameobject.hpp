#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QGraphicsRectItem>
#include <QTreeWidgetItem>

#include <memory>

class SpriteSet;

using RBShape = int;

struct RigidBody
{
  public:
    // Shape Information
    float       width;
    float       height;
    RBShape     shape_type;
    // General Information
    float       inv_mass;
    uint        force_mask;
    float       restitution;
    // Linear Information
    float       damping;
    QPointF     pos;
    QPointF     vel;
    QPointF     acc;
    // Rotational Information
    float       momentOfInertia;
    float       angle;
    float       angularVelocity;

  public:
    void        fromJson(const QJsonObject& json);
    QJsonObject toJson();

};

class GameObject;

struct AnimationGO
{
  public:
    int index;
    int current_anim;

  public:
    AnimationGO(GameObject* parent);

};

class GameObject : public QGraphicsPixmapItem, public QTreeWidgetItem
{
  private:
    QString                     m_Name;
    AnimationGO                 m_Animation;
    QSizeF                      m_Size;
    bool                        m_ResizeHorizontal;
    bool                        m_ResizeVertical;
    QPointF                     m_UV;
    std::unique_ptr<RigidBody>  m_RigidBody;
    QString                     m_SpriteSet;
    float                       m_Alpha;
    float                       m_R, m_G, m_B;
    QPixmap                     m_TintedImage;

  public:
    GameObject(const QPixmap& image);

    float r() const
    {
      return this->m_R;
    }

    float g() const
    {
      return this->m_G;
    }

    float b() const
    {
      return this->m_B;
    }

    void setR(float value)
    {
      if (value > 1) value = 1;
      if (value < 0) value = 0;
      this->m_R = value;
      this->update(this->boundingRect());
      updateTint();
    }

    void setG(float value)
    {
      if (value > 1) value = 1;
      if (value < 0) value = 0;
      this->m_G = value;
      this->update(this->boundingRect());
      updateTint();
    }

    void setB(float value)
    {
      if (value > 1) value = 1;
      if (value < 0) value = 0;
      this->m_B = value;
      this->update(this->boundingRect());
      updateTint();
    }

    qreal width() const
    {
      return this->m_Size.width();
    }

    void setWidth(const qreal value)
    {
      this->m_Size.setWidth(value);
      this->update(this->boundingRect());
    }

    qreal height() const
    {
      return this->m_Size.height();
    }

    void setHeight(const qreal value)
    {
      this->m_Size.setHeight(value);
      this->update(this->boundingRect());
    }

    void setAlpha(const float value);

    void fromJson(const QJsonObject& json);

    void toJson(QJsonObject& ret);

    const QString& name() const;
    void           setName(const QString& value);

    void setSelected(bool value);

  protected:
    QRect resizeH() const;
    QRect resizeV() const;
    QRect resizeHV() const;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

  public:
    void applySpriteSet(const SpriteSet& sSet, const bool setSize = true);
    void applyRigidBody(const QJsonObject& json);
    void applyRigidBody(std::nullptr_t);

    void setRect(qreal w, qreal h);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool contains(const QPointF &point) const override;
    QPainterPath opaqueArea() const override;
    QPainterPath shape() const override;

  public:
    QTreeWidgetItem* clone() const override;
    QVariant data(int column, int role) const override;
    void setData(int column, int role, const QVariant& value) override;

    ~GameObject() = default;

    int type() const override;

  public:
    void updateTint(void);


};
#endif // GAMEOBJECT_HPP
