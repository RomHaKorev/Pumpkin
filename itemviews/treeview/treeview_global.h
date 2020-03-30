#ifndef TREEVIEW_GLOBAL_H
#define TREEVIEW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TREEVIEW_LIBRARY)
#  define TREEVIEW_EXPORT Q_DECL_EXPORT
#else
#  define TREEVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // TREEVIEW_GLOBAL_H
