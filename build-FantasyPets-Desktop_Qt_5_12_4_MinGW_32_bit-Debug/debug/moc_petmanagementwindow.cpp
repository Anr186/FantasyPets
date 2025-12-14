/****************************************************************************
** Meta object code from reading C++ file 'petmanagementwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FantasyPets/petmanagementwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'petmanagementwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PetManagementWindow_t {
    QByteArrayData data[13];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PetManagementWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PetManagementWindow_t qt_meta_stringdata_PetManagementWindow = {
    {
QT_MOC_LITERAL(0, 0, 19), // "PetManagementWindow"
QT_MOC_LITERAL(1, 20, 17), // "backButtonClicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 10), // "petChanged"
QT_MOC_LITERAL(4, 50, 4), // "Pet*"
QT_MOC_LITERAL(5, 55, 3), // "pet"
QT_MOC_LITERAL(6, 59, 19), // "onFeedButtonClicked"
QT_MOC_LITERAL(7, 79, 19), // "onPlayButtonClicked"
QT_MOC_LITERAL(8, 99, 20), // "onSleepButtonClicked"
QT_MOC_LITERAL(9, 120, 19), // "onUndoButtonClicked"
QT_MOC_LITERAL(10, 140, 19), // "onBackButtonClicked"
QT_MOC_LITERAL(11, 160, 20), // "onRoomsButtonClicked"
QT_MOC_LITERAL(12, 181, 15) // "updatePetStatus"

    },
    "PetManagementWindow\0backButtonClicked\0"
    "\0petChanged\0Pet*\0pet\0onFeedButtonClicked\0"
    "onPlayButtonClicked\0onSleepButtonClicked\0"
    "onUndoButtonClicked\0onBackButtonClicked\0"
    "onRoomsButtonClicked\0updatePetStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PetManagementWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PetManagementWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PetManagementWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backButtonClicked(); break;
        case 1: _t->petChanged((*reinterpret_cast< Pet*(*)>(_a[1]))); break;
        case 2: _t->onFeedButtonClicked(); break;
        case 3: _t->onPlayButtonClicked(); break;
        case 4: _t->onSleepButtonClicked(); break;
        case 5: _t->onUndoButtonClicked(); break;
        case 6: _t->onBackButtonClicked(); break;
        case 7: _t->onRoomsButtonClicked(); break;
        case 8: _t->updatePetStatus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PetManagementWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetManagementWindow::backButtonClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PetManagementWindow::*)(Pet * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetManagementWindow::petChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PetManagementWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_PetManagementWindow.data,
    qt_meta_data_PetManagementWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PetManagementWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PetManagementWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PetManagementWindow.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PetObserver"))
        return static_cast< PetObserver*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PetManagementWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PetManagementWindow::backButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PetManagementWindow::petChanged(Pet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
