/****************************************************************************
** Meta object code from reading C++ file 'Garfield_control.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Control/Garfield_control.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Garfield_control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Garfield_control_t {
    QByteArrayData data[20];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Garfield_control_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Garfield_control_t qt_meta_stringdata_Garfield_control = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Garfield_control"
QT_MOC_LITERAL(1, 17, 12), // "poll_gamepad"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 19), // "update_acceleration"
QT_MOC_LITERAL(4, 51, 15), // "command_forward"
QT_MOC_LITERAL(5, 67, 12), // "command_back"
QT_MOC_LITERAL(6, 80, 19), // "command_forback_rel"
QT_MOC_LITERAL(7, 100, 12), // "command_left"
QT_MOC_LITERAL(8, 113, 13), // "command_right"
QT_MOC_LITERAL(9, 127, 21), // "command_leftright_rel"
QT_MOC_LITERAL(10, 149, 23), // "command_setForwardSpeed"
QT_MOC_LITERAL(11, 173, 5), // "value"
QT_MOC_LITERAL(12, 179, 20), // "command_setBackSpeed"
QT_MOC_LITERAL(13, 200, 20), // "command_setDirection"
QT_MOC_LITERAL(14, 221, 20), // "command_toggleLights"
QT_MOC_LITERAL(15, 242, 5), // "state"
QT_MOC_LITERAL(16, 248, 14), // "debug_settings"
QT_MOC_LITERAL(17, 263, 13), // "open_settings"
QT_MOC_LITERAL(18, 277, 15), // "closed_settings"
QT_MOC_LITERAL(19, 293, 21) // "open_close_connection"

    },
    "Garfield_control\0poll_gamepad\0\0"
    "update_acceleration\0command_forward\0"
    "command_back\0command_forback_rel\0"
    "command_left\0command_right\0"
    "command_leftright_rel\0command_setForwardSpeed\0"
    "value\0command_setBackSpeed\0"
    "command_setDirection\0command_toggleLights\0"
    "state\0debug_settings\0open_settings\0"
    "closed_settings\0open_close_connection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Garfield_control[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    1,  102,    2, 0x08 /* Private */,
      12,    1,  105,    2, 0x08 /* Private */,
      13,    1,  108,    2, 0x08 /* Private */,
      14,    1,  111,    2, 0x08 /* Private */,
      16,    1,  114,    2, 0x08 /* Private */,
      17,    0,  117,    2, 0x08 /* Private */,
      18,    0,  118,    2, 0x08 /* Private */,
      19,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Garfield_control::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Garfield_control *_t = static_cast<Garfield_control *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->poll_gamepad(); break;
        case 1: _t->update_acceleration(); break;
        case 2: _t->command_forward(); break;
        case 3: _t->command_back(); break;
        case 4: _t->command_forback_rel(); break;
        case 5: _t->command_left(); break;
        case 6: _t->command_right(); break;
        case 7: _t->command_leftright_rel(); break;
        case 8: _t->command_setForwardSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->command_setBackSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->command_setDirection((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->command_toggleLights((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->debug_settings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->open_settings(); break;
        case 14: _t->closed_settings(); break;
        case 15: _t->open_close_connection(); break;
        default: ;
        }
    }
}

const QMetaObject Garfield_control::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Garfield_control.data,
      qt_meta_data_Garfield_control,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Garfield_control::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Garfield_control::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Garfield_control.stringdata0))
        return static_cast<void*>(const_cast< Garfield_control*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Garfield_control::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
