/****************************************************************************
** Meta object code from reading C++ file 'checkoutmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../checkoutmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkoutmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CheckOutManager_t {
    QByteArrayData data[12];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CheckOutManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CheckOutManager_t qt_meta_stringdata_CheckOutManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CheckOutManager"
QT_MOC_LITERAL(1, 16, 25), // "on_btnSearchOrder_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 22), // "on_btnCheckOut_clicked"
QT_MOC_LITERAL(4, 66, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(5, 87, 20), // "on_tableView_clicked"
QT_MOC_LITERAL(6, 108, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 120, 5), // "index"
QT_MOC_LITERAL(8, 126, 26), // "on_tableView_doubleClicked"
QT_MOC_LITERAL(9, 153, 39), // "on_cmbPaymentMethod_currentIn..."
QT_MOC_LITERAL(10, 193, 28), // "on_leOrderSearch_textChanged"
QT_MOC_LITERAL(11, 222, 4) // "arg1"

    },
    "CheckOutManager\0on_btnSearchOrder_clicked\0"
    "\0on_btnCheckOut_clicked\0on_btnCancel_clicked\0"
    "on_tableView_clicked\0QModelIndex\0index\0"
    "on_tableView_doubleClicked\0"
    "on_cmbPaymentMethod_currentIndexChanged\0"
    "on_leOrderSearch_textChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CheckOutManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    1,   52,    2, 0x08 /* Private */,
       8,    1,   55,    2, 0x08 /* Private */,
       9,    1,   58,    2, 0x08 /* Private */,
      10,    1,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void CheckOutManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CheckOutManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnSearchOrder_clicked(); break;
        case 1: _t->on_btnCheckOut_clicked(); break;
        case 2: _t->on_btnCancel_clicked(); break;
        case 3: _t->on_tableView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_tableView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_cmbPaymentMethod_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_leOrderSearch_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CheckOutManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CheckOutManager.data,
    qt_meta_data_CheckOutManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CheckOutManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CheckOutManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CheckOutManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CheckOutManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
