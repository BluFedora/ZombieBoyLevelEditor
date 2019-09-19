#include "gameobject.hpp"
#include "spritesetlist.h"
#include "meta/propertytreeitem.hpp"

#include <QJsonObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>

#include <float.h>      /* FLT_MAX */
#include <math.h>

#include "meta/iclassproperty.h"

static void Json_pointf(QPointF& result, const QJsonObject& json)
{
  result.setX(json.value("x").toDouble(0.0));
  result.setY(json.value("y").toDouble(0.0));
}

void RigidBody::fromJson(const QJsonObject& json)
{
  this->width       = json.value("width").toDouble(100.0f);
  this->height      = json.value("height").toDouble(100.0f);
  this->shape_type  = json.value("shape_type").toInt(0);
  this->inv_mass    = json.value("mass").toDouble(1.0f);

  if (inv_mass == 0.0f) {
    inv_mass = FLT_MAX;
  } else if (inv_mass == FLT_MAX) {
    inv_mass = 0.0f;
  } else {
    inv_mass = 1.0f / inv_mass;
  }

  this->force_mask      = json.value("force_mask").toInt(0x00000000);
  this->restitution     = json.value("restitution").toDouble(0.95f);
  this->damping         = json.value("damping").toDouble(1.0f);
  Json_pointf(this->pos,  json.value("pos").toObject());
  Json_pointf(this->vel,  json.value("vel").toObject());
  Json_pointf(this->acc,  json.value("acc").toObject());
  this->angle           = json.value("angle").toDouble(0.0f);
  this->angularVelocity = json.value("angularVelocity").toDouble(0.0f);
}

QJsonObject RigidBody::toJson()
{
  QJsonObject obj;

  obj["width"] = width;
  obj["height"] = height;
  obj["shape_type"] = shape_type;
  obj["mass"] = inv_mass;
  obj["force_mask"] = (int)force_mask;
  obj["restitution"] = restitution;
  obj["damping"] = damping;
  obj["pos"] = QJsonObject{ {"x", pos.x() }, {"y", pos.y() } };
  obj["vel"] = QJsonObject{ {"x", vel.x() }, {"y", vel.y() } };
  obj["acc"] = QJsonObject{ {"x", acc.x() }, {"y", acc.y() } };
  obj["momentOfInertia"] = momentOfInertia;
  obj["angle"] = angle;
  obj["angularVelocity"] = angularVelocity;

  return obj;
}

GameObject::GameObject(const QPixmap& image) :
  QGraphicsPixmapItem(image, nullptr),
  QTreeWidgetItem(QStringList{"__k_", "GameObject_t"}, QGraphicsItem::UserType + 1),
  m_Name("New GameObject"),
  m_Animation(this),
  m_Size(100, 100),
  m_ResizeHorizontal(false),
  m_ResizeVertical(false),
  m_UV(1.0f, 1.0f),
  m_RigidBody(nullptr),
  m_SpriteSet(),
  m_Alpha(1.0f),
  m_R(1.0f),
  m_G(1.0f),
  m_B(1.0f),
  m_TintedImage(image)
{
  QGraphicsPixmapItem::setFlags(QGraphicsItem::ItemIsSelectable  |
                                QGraphicsItem::ItemIsMovable);
  QTreeWidgetItem::setFlags(Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable);

  setCacheMode(NoCache);

  auto prop_sprite = new PropertyTreeItem(this, "sprite", nullptr);

  auto prop_x_impl = IClassProperty<GameObject, qreal>::make(nullptr);
  prop_x_impl->addGetterSetter(&GameObject::x, &GameObject::setX);

  auto prop_y_impl = IClassProperty<GameObject, qreal>::make(nullptr);
  prop_y_impl->addGetterSetter(&GameObject::y, &GameObject::setY);

  auto prop_width_impl = IClassProperty<GameObject, qreal>::make(nullptr);
  prop_width_impl->addGetterSetter(&GameObject::width, &GameObject::setWidth);

  auto prop_height_impl = IClassProperty<GameObject, qreal>::make(nullptr);
  prop_height_impl->addGetterSetter(&GameObject::height, &GameObject::setHeight);

  auto prop_alpha_impl = IClassProperty<GameObject, float>::make(&GameObject::m_Alpha);
  prop_alpha_impl->addSetter(&GameObject::setAlpha);

  auto prop_rotation_impl = IClassProperty<GameObject, qreal>::make(nullptr);
  prop_rotation_impl->addGetterSetter(&GameObject::rotation, &GameObject::setRotation);

  auto prop_r_impl = IClassProperty<GameObject, float>::make(&GameObject::m_R);
  prop_r_impl->addGetterSetter(&GameObject::r, &GameObject::setR);
  auto prop_g_impl = IClassProperty<GameObject, float>::make(&GameObject::m_G);
  prop_g_impl->addGetterSetter(&GameObject::g, &GameObject::setG);
  auto prop_b_impl = IClassProperty<GameObject, float>::make(&GameObject::m_B);
  prop_b_impl->addGetterSetter(&GameObject::b, &GameObject::setB);

  prop_sprite->addChild(new PropertyTreeItem(this, "x",         prop_x_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "y",         prop_y_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "width",     prop_width_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "height",    prop_height_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "alpha",     prop_alpha_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "rotation",  prop_rotation_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "tint_r",    prop_r_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "tint_g",    prop_g_impl));
  prop_sprite->addChild(new PropertyTreeItem(this, "tint_b",    prop_b_impl));

  this->addChild(prop_sprite);
}

void GameObject::setAlpha(const float value)
{
  this->m_Alpha = fmin(fmax(value, 0.0f), 1.0f);
  this->update(this->boundingRect());
}

void GameObject::fromJson(const QJsonObject& json)
{
   QJsonObject animation = json.value("animation").toObject();

  this->m_Animation.current_anim = animation.value("current_anim").toInt(0);
  this->m_Animation.index = animation.value("index").toInt(0);

  this->setName(json.value("name").toString(this->name()));
  QJsonObject sprite = json.value("sprite").toObject();
  this->setX(sprite.value("positionX").toDouble(0.0));
  this->setY(sprite.value("positionY").toDouble(0.0));
  this->m_Alpha = sprite.value("alpha").toDouble(0.0);
  this->m_R = sprite.value("r").toDouble(1.0);
  this->m_G = sprite.value("g").toDouble(1.0);
  this->m_B = sprite.value("b").toDouble(1.0);
  this->setRotation(sprite.value("rotation").toDouble(0.0));
  this->setRect(sprite.value("width").toDouble(100.0),
                sprite.value("height").toDouble(100.0));

  if (json.contains("rigidbody"))
  {
    QJsonObject rigidbody = json.value("rigidbody").toObject();
    this->applyRigidBody(rigidbody);
  }
}

void GameObject::toJson(QJsonObject& ret)
{
  ret.insert("name", QJsonValue(this->name()));

  ret["animation"] = QJsonObject{
  {"delta_time", 0.0},
  {"current_anim", this->m_Animation.current_anim },
  {"index", this->m_Animation.index  }
};

  ret["sprite"] = QJsonObject{
  {"positionX", this->x()},
  {"positionY", this->y()},
  {"alpha",     this->m_Alpha },
  {"width",     this->m_Size.width() },
  {"height",    this->m_Size.height() },
  {"rotation",  this->rotation() },
  {"uvX",       0.0 },
  {"uvY",       0.0 },
  {"r",         this->m_R },
  {"g",         this->m_G },
  {"b",         this->m_B },
  {"spriteSet", this->m_SpriteSet}
};

  if (this->m_RigidBody) {
    this->m_RigidBody->pos = this->pos();
    ret["rigidbody"] = this->m_RigidBody->toJson();
  }
}

const QString&GameObject::name() const { return this->m_Name; }

void GameObject::setName(const QString& value)
{
  this->m_Name = value;
}

void GameObject::setSelected(bool value)
{
  QGraphicsPixmapItem::setSelected(value);
  QTreeWidgetItem::setSelected(value);
}

QRect GameObject::resizeH() const
{
  return QRect(m_Size.width() - 20,
               0,
               20,
               this->m_Size.height() - 25);
}

QRect GameObject::resizeV() const
{
  return QRect(0,
               m_Size.height() - 20,
               m_Size.width() - 25,
               20);
}

QRect GameObject::resizeHV() const
{
  return QRect(m_Size.width()  - 20,
               m_Size.height() - 20,
               20,
               20);
}

void GameObject::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsPixmapItem::mousePressEvent(event);

  if(event->button() == Qt::LeftButton)
  {
    if(event->modifiers() & Qt::AltModifier)
    {
      const auto pointToCheck = event->scenePos();
      auto rectToCheck = this->resizeHV();

      if (rectToCheck.contains(pointToCheck.x() - this->x(), pointToCheck.y() - this->y()))
      {
        this->m_ResizeVertical = true;
        this->m_ResizeHorizontal = true;
      }
      else
      {
        rectToCheck = this->resizeH();

        if (rectToCheck.contains(pointToCheck.x() - this->x(), pointToCheck.y() - this->y()))
        {
          this->m_ResizeHorizontal = true;
        }
        else
        {
          this->m_ResizeHorizontal = false;
        }

        rectToCheck = this->resizeV();

        if (rectToCheck.contains(pointToCheck.x() - this->x(), pointToCheck.y() - this->y()))
        {
          this->m_ResizeVertical = true;
        }
        else
        {
          this->m_ResizeVertical = false;
        }
      }

      event->accept();
    }
    else
    {
      qDebug() << "GO item left clicked.";
      event->accept();
    }
  }
  else if(event->button() == Qt::RightButton) {
    qDebug() << "GO item right clicked.";
    event->ignore();
  }
}

void GameObject::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if(event->modifiers() & Qt::AltModifier)
  {
    QPointF pos = event->scenePos();
    bool keep_ratio = (event->modifiers() & Qt::ShiftModifier);
    float ratio_w = 0.0f, ratio_h = 0.0f;

    if (keep_ratio) {
      ratio_w = this->boundingRect().width() / this->boundingRect().height();
      ratio_h = this->boundingRect().height() / this->boundingRect().width();
    }

    if (this->m_ResizeHorizontal)
    {
      auto newWidth = pos.x() - this->x();
      if (newWidth < 10) newWidth = 10;
      this->m_Size.setWidth(newWidth);

      if (keep_ratio) {
        this->m_Size.setHeight(ratio_h * newWidth);
      }
    }

    if (m_ResizeVertical)
    {
      auto newHeight = pos.y() - this->y();
      if (newHeight < 10) newHeight = 10;
      this->m_Size.setHeight(newHeight);

      if (keep_ratio) {
        this->m_Size.setWidth(ratio_w * newHeight);
      }
    }

    this->update(this->boundingRect());
  }
  else
  {
    QGraphicsPixmapItem::mouseMoveEvent(event);
  }
}

void GameObject::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  this->m_ResizeHorizontal = false;
  this->m_ResizeVertical = false;
  QGraphicsItem::mouseReleaseEvent(event);
}

void GameObject::dropEvent(QGraphicsSceneDragDropEvent* event)
{
  qDebug() << "Something was dropped on this GameObject";
  event->accept();
}

QVariant GameObject::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
  if (change == ItemSelectedChange)
  {
    QTreeWidgetItem::setSelected(value.toBool());
  }

  return QGraphicsPixmapItem::itemChange(change, value);
}

void GameObject::applySpriteSet(const SpriteSet& sSet, const bool setSize)
{
  this->m_SpriteSet = sSet.name;
  this->setPixmap(sSet.texture);
  this->m_UV.setX(1.0f / sSet.numCols);
  this->m_UV.setY(1.0f / sSet.numRows);
  if (setSize)
    this->setRect(sSet.texture.width() * this->m_UV.x(), sSet.texture.height() * this->m_UV.y());
  else
    this->update(this->boundingRect());
  this->updateTint();
}

void GameObject::applyRigidBody(const QJsonObject& json)
{
  this->m_RigidBody.reset(new RigidBody());
  this->m_RigidBody->fromJson(json);
  this->update(this->boundingRect());
}

void GameObject::applyRigidBody(std::nullptr_t)
{
  this->m_RigidBody.release();
  this->update(this->boundingRect());
}

void GameObject::setRect(qreal w, qreal h)
{
  this->m_Size.setWidth(w);
  this->m_Size.setHeight(h);
  this->update(this->boundingRect());
}

QRectF GameObject::boundingRect() const
{
  return QRectF(0, 0, this->m_Size.width(), this->m_Size.height());
}

void GameObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  (void) option;
  (void) widget;

  if (!this->pixmap().isNull()) {
    auto source = this->pixmap().rect();
    auto dest = this->boundingRect().toRect();

    source.setWidth(source.width()   * this->m_UV.x());
    source.setHeight(source.height() * this->m_UV.y());

    painter->setOpacity(this->m_Alpha);
    painter->setBackgroundMode(Qt::TransparentMode);
    painter->drawPixmap(dest, this->m_TintedImage, source);
  }

  if (this->m_RigidBody)
  {
    painter->setPen(QPen(Qt::green, 2));
    painter->drawRect(0, 0, this->m_RigidBody->width, this->m_RigidBody->height);
  }

  painter->setPen(QPen(Qt::red, 2));
  if (QGraphicsPixmapItem::isSelected()) {
    painter->setPen(QPen(Qt::blue, 2, Qt::DotLine));
  }
  painter->drawRect(this->boundingRect());
  painter->setPen(QPen(Qt::red, 1));
  painter->drawRect(this->resizeH());
  painter->drawRect(this->resizeV());
  painter->drawRect(this->resizeHV());
}

bool GameObject::contains(const QPointF& point) const
{
  return this->boundingRect().contains(point);
}

QPainterPath GameObject::opaqueArea() const
{
  QPainterPath path;
  path.addRect(this->boundingRect());
  return path;
}

QPainterPath GameObject::shape() const
{
  return this->opaqueArea();
}

QTreeWidgetItem* GameObject::clone() const
{
  return new GameObject(this->pixmap());
}

QVariant GameObject::data(int column, int role) const
{
  if (column == 0)
  {
    if (role == Qt::DisplayRole)
    {
      return this->name();
    }
    else if (role == Qt::DecorationRole)
    {
      if (!this->pixmap().isNull())
        return this->pixmap().scaled(QSize(16, 16));
    }
    else if (role == Qt::EditRole)
    {
      return this->name();
    }
  }

  return QTreeWidgetItem::data(column, role);
}

void GameObject::setData(int column, int role, const QVariant& value)
{
  qDebug() << "Role: " << role << " Value: " << value;

  if (column == 0) {
    if (role == Qt::EditRole) {
      this->setName(value.toString());
    } else {
      QTreeWidgetItem::setData(column, role, value);
    }
  }
}

int GameObject::type() const
{
  return QGraphicsItem::UserType + 1;
}

void GameObject::updateTint()
{
  if (this->pixmap().isNull()) return;

   auto source = this->pixmap().rect();
  QPainter p;

  QImage img(this->pixmap().toImage());
  QImage mask(img);
  QColor color;
  color.setRgb(this->m_R * 255, this->m_G * 255, this->m_B * 255);

  p.begin(&mask);
  p.setCompositionMode(QPainter::CompositionMode_SourceIn);
  p.fillRect(source, color);
  p.end();

  p.begin(&img);
  p.setCompositionMode(QPainter::CompositionMode_Multiply);
  p.drawImage(0, 0, mask);
  p.end();

  this->m_TintedImage = QPixmap::fromImage(img);
}

AnimationGO::AnimationGO(GameObject* parent) :
  index(0),
  current_anim(-1)
{
  auto prop_animation = new PropertyTreeItem(this, "animation", nullptr);

  auto prop_index_impl = IClassProperty<AnimationGO, int>::make(&AnimationGO::index);
  auto prop_current_anim_impl = IClassProperty<AnimationGO, int>::make(&AnimationGO::current_anim);

  prop_animation->addChild(new PropertyTreeItem(this, "index", prop_index_impl));
  prop_animation->addChild(new PropertyTreeItem(this, "current_anim", prop_current_anim_impl));

  parent->addChild(prop_animation);
}
