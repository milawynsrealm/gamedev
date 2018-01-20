#ifndef SHARED_H
#define SHARED_H

#ifdef(_WIN32)
#include <wchar.h>
#else
typedef char WCHAR;
typedef unsigned __int64 DWORDLONG;
#endif /* _WIN32 */

/* Used to identify the OS type */
#define OSNAME_NONE    -1
#define OSNAME_WINDOWS  0
#define OSNAME_LINUX    1
#define OSNAME_BSD      2
#define OSNAME_MACOS    3
#define OSNAME_ANDROID  4
#define OSNAME_BEOS     5
#define OSNAME_OS2      6

/* Used to determine the Architecture type */
#define ARCH_NONE    -1
#define ARCH_86      0
#define ARCH_AMD64   1
#define ARCH_ITANIUM 2
#define ARCH_ARM     3
#define ARCH_ALPHA   4
#define ARCH_PPC     5

#endif /* SHARED_H */
