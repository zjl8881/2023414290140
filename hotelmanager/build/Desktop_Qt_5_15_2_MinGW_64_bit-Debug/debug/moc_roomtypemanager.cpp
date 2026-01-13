/****************************************************************************
** Meta object code from reading C++ file 'roomtypemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../roomtypemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'roomtypemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RoomTypeManager_t {
    QByteArrayData data[13];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RoomTypeManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RoomTypeManager_t qt_meta_stringdata_RoomTypeManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "RoomTypeManager"
QT_MOC_LITERAL(1, 16, 17), // "on_btnAdd_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "on_btnEdit_clicked"
QT_MOC_LITERAL(4, 54, 20), // "on_btnDelete_clicked"
QT_MOC_LITERAL(5, 75, 21), // "on_btnRefresh_clicked"
QT_MOC_LITERAL(6, 97, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(7, 117, 26), // "on_tableView_doubleClicked"
QT_MOC_LITERAL(8, 144, 11), // "QModelIndex"
QT_MOC_LITERAL(9, 156, 5), // "index"
QT_MOC_LITERAL(10, 162, 20), // "on_btnSearch_clicked"
QT_MOC_LITERAL(11, 183, 23), // "on_leSearch_textChanged"
QT_MOC_LITERAL(12, 207, 4) // "arg1"

    },
    "RoomTypeManager\0on_btnAdd_clicked\0\0"
    "on_btnEdit_clicked\0on_btnDelete_clicked\0"
    "on_btnRefresh_clicked\0on_btnClose_clicked\0"
    "on_tableView_doubleClicked\0QModelIndex\0"
    "index\0on_btnSearch_clicked\0"
    "on_leSearch_textChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RoomTypeManager[] = {

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
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    1,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void RoomTypeManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RoomTypeManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnAdd_clicked(); break;
        case 1: _t->on_btnEdit_clicked(); break;
        case 2: _t->on_btnDelete_clicked(); break;
        case 3: _t->on_btnRefresh_clicked(); break;
        case 4: _t->on_btnClose_clicked(); break;
        case 5: _t->on_tableView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_btnSearch_clicked(); break;
        case 7: _t->on_leSearch_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RoomTypeManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_RoomTypeManager.data,
    qt_meta_data_RoomTypeManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RoomTypeManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RoomTypeManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RoomTypeManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RoomTypeManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
