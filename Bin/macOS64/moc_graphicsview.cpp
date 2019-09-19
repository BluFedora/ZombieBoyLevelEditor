/****************************************************************************
** Meta object code from reading C++ file 'graphicsview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../zombie_hoarde_le/graphicsview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphicsView_t {
    QByteArrayData data[7];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsView_t qt_meta_stringdata_GraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GraphicsView"
QT_MOC_LITERAL(1, 13, 15), // "doAddGameObject"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "texture"
QT_MOC_LITERAL(4, 38, 17), // "doAttachRigidBody"
QT_MOC_LITERAL(5, 56, 19), // "doDeleteGameObjects"
QT_MOC_LITERAL(6, 76, 17) // "doRemoveRigidBody"

    },
    "GraphicsView\0doAddGameObject\0\0texture\0"
    "doAttachRigidBody\0doDeleteGameObjects\0"
    "doRemoveRigidBody"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,
       6,    0,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPixmap,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphicsView *_t = static_cast<GraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doAddGameObject((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 1: _t->doAttachRigidBody(); break;
        case 2: _t->doDeleteGameObjects(); break;
        case 3: _t->doRemoveRigidBody(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphicsView::*_t)(const QPixmap & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::doAddGameObject)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::doAttachRigidBody)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::doDeleteGameObjects)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::doRemoveRigidBody)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject GraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphicsView.data,
      qt_meta_data_GraphicsView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsView.stringdata0))
        return static_cast<void*>(const_cast< GraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GraphicsView::doAddGameObject(const QPixmap & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphicsView::doAttachRigidBody()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void GraphicsView::doDeleteGameObjects()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void GraphicsView::doRemoveRigidBody()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
