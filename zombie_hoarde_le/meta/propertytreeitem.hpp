#ifndef PROPERTYTREEITEM_HPP
#define PROPERTYTREEITEM_HPP

#include <QTreeWidgetItem>

class IClassPropertyBase;

class PropertyTreeItem : public QTreeWidgetItem
{
  public:
    void*               m_Object;
    QString             m_Key;
    IClassPropertyBase* m_Property;
  public:
    PropertyTreeItem(void* object, const QString& key, IClassPropertyBase* property);

  public:
    QTreeWidgetItem*  clone() const override;
    QVariant          data(int column, int role) const override;
    void              setData(int column, int role, const QVariant& value) override;

    ~PropertyTreeItem();

};

#endif // PROPERTYTREEITEM_HPP
