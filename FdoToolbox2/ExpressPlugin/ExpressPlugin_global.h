#ifndef EXPRESSPLUGIN_GLOBAL_H
#define EXPRESSPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EXPRESSPLUGIN_LIBRARY)
#  define EXPRESSPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EXPRESSPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPRESSPLUGIN_GLOBAL_H
