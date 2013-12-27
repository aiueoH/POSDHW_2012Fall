/****************************************************************************
** Meta object code from reading C++ file 'GraphUI.h'
**
** Created: Wed Feb 20 14:52:16 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GraphUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      47,    8,    8,    8, 0x0a,
      85,    8,    8,    8, 0x0a,
     133,    8,    8,    8, 0x0a,
     168,    8,    8,    8, 0x0a,
     203,    8,    8,    8, 0x0a,
     240,    8,    8,    8, 0x0a,
     281,    8,    8,    8, 0x0a,
     326,    8,    8,    8, 0x0a,
     370,    8,    8,    8, 0x0a,
     412,    8,    8,    8, 0x0a,
     449,    8,    8,    8, 0x0a,
     483,    8,    8,    8, 0x0a,
     517,    8,    8,    8, 0x0a,
     553,    8,    8,    8, 0x0a,
     587,    8,    8,    8, 0x0a,
     620,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphUI[] = {
    "GraphUI\0\0toolBarButtonOpenFile_clickListener()\0"
    "toolBarButtonSaveFile_clickListener()\0"
    "toolBarButtonIsExistPathBetween_clickListener()\0"
    "toolBarButtonClose_clickListener()\0"
    "toolBarButtonPoint_clickListener()\0"
    "toolBarButtonConnect_clickListener()\0"
    "toolBarButtonAddActivity_clickListener()\0"
    "toolBarButtonAddDecisionNode_clickListener()\0"
    "toolBarButtonAddInitialNode_clickListener()\0"
    "toolBarButtonAddFinalNode_clickListener()\0"
    "toolBarButtonAddEdge_clickListener()\0"
    "toolBarButtonRedo_clickListener()\0"
    "toolBarButtonUndo_clickListener()\0"
    "toolBarButtonDelete_clickListener()\0"
    "toolBarButtonCopy_clickListener()\0"
    "toolBarButtonCut_clickListener()\0"
    "toolBarButtonPaste_clickListener()\0"
};

void GraphUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GraphUI *_t = static_cast<GraphUI *>(_o);
        switch (_id) {
        case 0: _t->toolBarButtonOpenFile_clickListener(); break;
        case 1: _t->toolBarButtonSaveFile_clickListener(); break;
        case 2: _t->toolBarButtonIsExistPathBetween_clickListener(); break;
        case 3: _t->toolBarButtonClose_clickListener(); break;
        case 4: _t->toolBarButtonPoint_clickListener(); break;
        case 5: _t->toolBarButtonConnect_clickListener(); break;
        case 6: _t->toolBarButtonAddActivity_clickListener(); break;
        case 7: _t->toolBarButtonAddDecisionNode_clickListener(); break;
        case 8: _t->toolBarButtonAddInitialNode_clickListener(); break;
        case 9: _t->toolBarButtonAddFinalNode_clickListener(); break;
        case 10: _t->toolBarButtonAddEdge_clickListener(); break;
        case 11: _t->toolBarButtonRedo_clickListener(); break;
        case 12: _t->toolBarButtonUndo_clickListener(); break;
        case 13: _t->toolBarButtonDelete_clickListener(); break;
        case 14: _t->toolBarButtonCopy_clickListener(); break;
        case 15: _t->toolBarButtonCut_clickListener(); break;
        case 16: _t->toolBarButtonPaste_clickListener(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GraphUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GraphUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GraphUI,
      qt_meta_data_GraphUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphUI))
        return static_cast<void*>(const_cast< GraphUI*>(this));
    if (!strcmp(_clname, "Observer"))
        return static_cast< Observer*>(const_cast< GraphUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GraphUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
