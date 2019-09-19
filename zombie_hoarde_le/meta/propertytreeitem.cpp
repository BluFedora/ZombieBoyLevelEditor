#include "iclassproperty.h"
#include "propertytreeitem.hpp"

PropertyTreeItem::PropertyTreeItem(void* object, const QString& key, IClassPropertyBase* property) :
  QTreeWidgetItem(QStringList{key, "value"}, QTreeWidgetItem::UserType + 2),
  m_Object(object),
  m_Key(key),
  m_Property(property)
{
  this->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
}

QTreeWidgetItem* PropertyTreeItem::clone() const
{
  return new PropertyTreeItem(this->m_Object, this->m_Key, this->m_Property);
}

QVariant PropertyTreeItem::data(int column, int role) const
{
  switch (column)
  {
    case 0:
      {
        switch (role)
        {
          case Qt::EditRole:
            return QVariant();
            break;
          case Qt::DisplayRole:
            return this->m_Key;
            break;
        }
        break;
      }
    case 1:
      {
        switch (role)
        {
          case Qt::EditRole:
          case Qt::DisplayRole:
            if (this->m_Property)
              return this->m_Property->getValue(this->m_Object);
            return "struct";
            break;
        }

        break;
      }
  }

  return QVariant();
}

void PropertyTreeItem::setData(int column, int role, const QVariant& value)
{
  switch (column)
  {
    case 0:
      {
        /* IGNORED */
        break;
      }
    case 1:
      {
        switch (role)
        {
          case Qt::EditRole:
          case Qt::DisplayRole:
            if (this->m_Property)
              this->m_Property->setValue(this->m_Object, value);
            break;
        }

        break;
      }
  }
}

PropertyTreeItem::~PropertyTreeItem()
{
  delete this->m_Property;
}
