/****************************************************************************
** Meta object code from reading C++ file 'dllsarjaportti.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DLLSarjaPortti/dllsarjaportti.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dllsarjaportti.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DLLSarjaPortti_t {
    QByteArrayData data[5];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DLLSarjaPortti_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DLLSarjaPortti_t qt_meta_stringdata_DLLSarjaPortti = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DLLSarjaPortti"
QT_MOC_LITERAL(1, 15, 12), // "readComplete"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 2), // "id"
QT_MOC_LITERAL(4, 32, 9) // "writeData"

    },
    "DLLSarjaPortti\0readComplete\0\0id\0"
    "writeData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DLLSarjaPortti[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DLLSarjaPortti::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DLLSarjaPortti *_t = static_cast<DLLSarjaPortti *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readComplete((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->writeData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DLLSarjaPortti::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DLLSarjaPortti::readComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DLLSarjaPortti::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DLLSarjaPortti.data,
      qt_meta_data_DLLSarjaPortti,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DLLSarjaPortti::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DLLSarjaPortti::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DLLSarjaPortti.stringdata0))
        return static_cast<void*>(const_cast< DLLSarjaPortti*>(this));
    return QObject::qt_metacast(_clname);
}

int DLLSarjaPortti::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DLLSarjaPortti::readComplete(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
