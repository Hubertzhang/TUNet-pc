#ifndef QTHPPLE_GLOBAL_H
#define QTHPPLE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTHPPLE_LIBRARY)
#  define QTHPPLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTHPPLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTHPPLE_GLOBAL_H
