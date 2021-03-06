/*
    Copyright (c) 2018-2019, Lee Schroeder
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
          names of its contributors may be used to endorse or promote products
          derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL LEE SCHROEDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef PATH_H
#define PATH_H

#include <stdio.h>
#include "shared.h"

#if (CURRENT_OS == OSNAME_WINDOWS)
#include "win32/path.h"
#else
#include "posix/path.h"
#endif /* _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

/* Windows uses a different path separator 
   than other operating systems. */
UNICHAR *GetSystemDirSeperator(void)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return L'\\';
#else
    return '/';
#endif /* _WIN32 */
}

/* Grabs the user's home directory path used commonly for 
   application settings and save files */
int GetPathConfigDirectory(UNICHAR *path, UNICHAR *folderName)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return GetPathConfigDirectory_win32(&path, &folderName);
#else
    return GetPathConfigDirectory_posix(&path, &folderName);
#endif /* _WIN32 */
}

/* Grabs the path of the application's current 
   directory */
int GetPathAppDirectory(UNICHAR *path)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return GetPathAppDirectory_win32(&path);
#else
    return GetPathAppDirectory_posix(&path);
#endif /* _WIN32 */
}

/* Grabs the path used to create temporary files
   used by programs to run faster */
int GetPathTempDirectory(UNICHAR *path)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return GetPathTempDirectory_win32(&path);
#else
    return GetPathTempDirectory_posix(&path);
#endif /* _WIN32 */
}

#ifdef __cplusplus
}
#endif

#endif /* PATH_H */
