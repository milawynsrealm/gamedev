#ifndef STRING_H
#define STRING_H

#ifdef(_WIN32)
#include <wchar.h>
#else
typedef WCHAR char;
#endif /* _WIN32 */

#endif /* STRING_H */
