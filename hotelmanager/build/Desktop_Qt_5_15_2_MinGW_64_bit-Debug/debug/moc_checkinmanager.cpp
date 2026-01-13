/****************************************************************************
** Meta object code from reading C++ file 'checkinmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../checkinmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkinmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CheckInManager_t {
    QByteArrayData data[12];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CheckInManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CheckInManager_t qt_meta_stringdata_CheckInManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CheckInManager"
QT_MOC_LITERAL(1, 15, 21), // "on_btnCheckIn_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(4, 59, 21), // "on_btnRefresh_clicked"
QT_MOC_LITERAL(5, 81, 34), // "on_cmbRoomType_currentIndexCh..."
QT_MOC_LITERAL(6, 116, 5), // "index"
QT_MOC_LITERAL(7, 122, 30), // "on_cmbRoom_currentIndexChanged"
QT_MOC_LITERAL(8, 153, 24), // "on_deCheckIn_dateChanged"
QT_MOC_LITERAL(9, 178, 4), // "date"
QT_MOC_LITERAL(10, 183, 25), // "on_deCheckOut_dateChanged"
QT_MOC_LITERAL(11, 209, 28) // "on_btnSearchCustomer_clicked"

    },
    "CheckInManager\0on_btnCheckIn_clicked\0"
    "\0on_btnCancel_clicked\0on_btnRefresh_clicked\0"
    "on_cmbRoomType_currentIndexChanged\0"
    "index\0on_cmbRoom_currentIndexChanged\0"
    "on_deCheckIn_dateChanged\0date\0"
    "on_deCheckOut_dateChanged\0"
    "on_btnSearchCustomer_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CheckInManager[] = {

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
       7,    1,   60,    2, 0x08 /* Private */,
       8,    1,   63,    2, 0x08 /* Private */,
      10,    1,   66,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QDate,    9,
    QMetaType::Void, QMetaType::QDate,    9,
    QMetaType::Void,

       0        // eod
};

void CheckInManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CheckInManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnCheckIn_clicked(); break;
        case 1: _t->on_btnCancel_clicked(); break;
        case 2: _t->on_btnRefresh_clicked(); break;
        case 3: _t->on_cmbRoomType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_cmbRoom_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_deCheckIn_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 6: _t->on_deCheckOut_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 7: _t->on_btnSearchCustomer_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CheckInManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CheckInManager.data,
    qt_meta_data_CheckInManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CheckInManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CheckInManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CheckInManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CheckInManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
