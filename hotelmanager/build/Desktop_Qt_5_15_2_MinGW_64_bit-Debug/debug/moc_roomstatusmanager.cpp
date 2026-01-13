/****************************************************************************
** Meta object code from reading C++ file 'roomstatusmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../roomstatusmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'roomstatusmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RoomStatusManager_t {
    QByteArrayData data[12];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RoomStatusManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RoomStatusManager_t qt_meta_stringdata_RoomStatusManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "RoomStatusManager"
QT_MOC_LITERAL(1, 18, 21), // "on_btnRefresh_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(4, 61, 14), // "onTimerTimeout"
QT_MOC_LITERAL(5, 76, 20), // "on_tableView_clicked"
QT_MOC_LITERAL(6, 97, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 109, 5), // "index"
QT_MOC_LITERAL(8, 115, 26), // "on_tableView_doubleClicked"
QT_MOC_LITERAL(9, 142, 32), // "on_cmbStatus_currentIndexChanged"
QT_MOC_LITERAL(10, 175, 31), // "on_cmbFloor_currentIndexChanged"
QT_MOC_LITERAL(11, 207, 34) // "on_cmbRoomType_currentIndexCh..."

    },
    "RoomStatusManager\0on_btnRefresh_clicked\0"
    "\0on_btnClose_clicked\0onTimerTimeout\0"
    "on_tableView_clicked\0QModelIndex\0index\0"
    "on_tableView_doubleClicked\0"
    "on_cmbStatus_currentIndexChanged\0"
    "on_cmbFloor_currentIndexChanged\0"
    "on_cmbRoomType_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RoomStatusManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       8,    1,   60,    2, 0x08 /* Private */,
       9,    1,   63,    2, 0x08 /* Private */,
      10,    1,   66,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void RoomStatusManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RoomStatusManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnRefresh_clicked(); break;
        case 1: _t->on_btnClose_clicked(); break;
        case 2: _t->onTimerTimeout(); break;
        case 3: _t->on_tableView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_tableView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_cmbStatus_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_cmbFloor_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_cmbRoomType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RoomStatusManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_RoomStatusManager.data,
    qt_meta_data_RoomStatusManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RoomStatusManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RoomStatusManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RoomStatusManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RoomStatusManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
