#ifndef SUMBLOCK_GLOBAL_H
#define SUMBLOCK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SUMBLOCK_LIBRARY)
#  define SUMBLOCKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SUMBLOCKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SUMBLOCK_GLOBAL_H
