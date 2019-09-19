/****************************************************************************
** Meta object code from reading C++ file 'zombiehordele.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../zombie_hoarde_le/zombiehordele.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zombiehordele.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZombieHordeScene_t {
    QByteArrayData data[7];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZombieHordeScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZombieHordeScene_t qt_meta_stringdata_ZombieHordeScene = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ZombieHordeScene"
QT_MOC_LITERAL(1, 17, 15), // "doAddGameObject"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "texture"
QT_MOC_LITERAL(4, 42, 15), // "attachRigidBody"
QT_MOC_LITERAL(5, 58, 15), // "removeRigidBody"
QT_MOC_LITERAL(6, 74, 19) // "deleteSelectedItems"

    },
    "ZombieHordeScene\0doAddGameObject\0\0"
    "texture\0attachRigidBody\0removeRigidBody\0"
    "deleteSelectedItems"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZombieHordeScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x0a /* Public */,
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPixmap,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZombieHordeScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZombieHordeScene *_t = static_cast<ZombieHordeScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doAddGameObject((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 1: _t->attachRigidBody(); break;
        case 2: _t->removeRigidBody(); break;
        case 3: _t->deleteSelectedItems(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZombieHordeScene::*_t)(const QPixmap & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZombieHordeScene::doAddGameObject)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ZombieHordeScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_ZombieHordeScene.data,
      qt_meta_data_ZombieHordeScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZombieHordeScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZombieHordeScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZombieHordeScene.stringdata0))
        return static_cast<void*>(const_cast< ZombieHordeScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int ZombieHordeScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
void ZombieHordeScene::doAddGameObject(const QPixmap & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ZombieHordeLE_t {
    QByteArrayData data[7];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZombieHordeLE_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZombieHordeLE_t qt_meta_stringdata_ZombieHordeLE = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ZombieHordeLE"
QT_MOC_LITERAL(1, 14, 14), // "onSetAssetPath"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "onAddGameObject"
QT_MOC_LITERAL(4, 46, 19), // "onDeleteGameObjects"
QT_MOC_LITERAL(5, 66, 11), // "onSaveLevel"
QT_MOC_LITERAL(6, 78, 11) // "onLoadLevel"

    },
    "ZombieHordeLE\0onSetAssetPath\0\0"
    "onAddGameObject\0onDeleteGameObjects\0"
    "onSaveLevel\0onLoadLevel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZombieHordeLE[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZombieHordeLE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZombieHordeLE *_t = static_cast<ZombieHordeLE *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSetAssetPath(); break;
        case 1: _t->onAddGameObject(); break;
        case 2: _t->onDeleteGameObjects(); break;
        case 3: _t->onSaveLevel(); break;
        case 4: _t->onLoadLevel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZombieHordeLE::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ZombieHordeLE.data,
      qt_meta_data_ZombieHordeLE,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZombieHordeLE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZombieHordeLE::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZombieHordeLE.stringdata0))
        return static_cast<void*>(const_cast< ZombieHordeLE*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ZombieHordeLE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
