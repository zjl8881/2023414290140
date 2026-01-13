/****************************************************************************
** Meta object code from reading C++ file 'ordermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ordermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ordermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OrderManager_t {
    QByteArrayData data[14];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OrderManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OrderManager_t qt_meta_stringdata_OrderManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OrderManager"
QT_MOC_LITERAL(1, 13, 20), // "on_btnSearch_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 25), // "on_btnResetFilter_clicked"
QT_MOC_LITERAL(4, 61, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(5, 81, 20), // "on_tableView_clicked"
QT_MOC_LITERAL(6, 102, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 114, 5), // "index"
QT_MOC_LITERAL(8, 120, 26), // "on_tableView_doubleClicked"
QT_MOC_LITERAL(9, 147, 26), // "on_deStartDate_dateChanged"
QT_MOC_LITERAL(10, 174, 4), // "date"
QT_MOC_LITERAL(11, 179, 24), // "on_deEndDate_dateChanged"
QT_MOC_LITERAL(12, 204, 28), // "on_leOrderSearch_textChanged"
QT_MOC_LITERAL(13, 233, 4) // "arg1"

    },
    "OrderManager\0on_btnSearch_clicked\0\0"
    "on_btnResetFilter_clicked\0on_btnClose_clicked\0"
    "on_tableView_clicked\0QModelIndex\0index\0"
    "on_tableView_doubleClicked\0"
    "on_deStartDate_dateChanged\0date\0"
    "on_deEndDate_dateChanged\0"
    "on_leOrderSearch_textChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OrderManager[] = {

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
      11,    1,   66,    2, 0x08 /* Private */,
      12,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QDate,   10,
    QMetaType::Void, QMetaType::QDate,   10,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void OrderManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OrderManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnSearch_clicked(); break;
        case 1: _t->on_btnResetFilter_clicked(); break;
        case 2: _t->on_btnClose_clicked(); break;
        case 3: _t->on_tableView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_tableView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_deStartDate_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 6: _t->on_deEndDate_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 7: _t->on_leOrderSearch_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OrderManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_OrderManager.data,
    qt_meta_data_OrderManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OrderManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OrderManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OrderManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int OrderManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
