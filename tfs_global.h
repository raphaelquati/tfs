#ifndef TFS_GLOBAL_H
#define TFS_GLOBAL_H

#include <QtGlobal>

#if defined(TFS_LIBRARY)
#  define TFSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TFSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TFS_GLOBAL_H

