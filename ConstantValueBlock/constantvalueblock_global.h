#ifndef CONSTANTVALUEBLOCK_GLOBAL_H
#define CONSTANTVALUEBLOCK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONSTANTVALUEBLOCK_LIBRARY)
#  define CONSTANTVALUEBLOCKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONSTANTVALUEBLOCKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONSTANTVALUEBLOCK_GLOBAL_H
