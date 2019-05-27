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
#ifndef PATH_WIN32_H
#ifndef PATH_WIN32_H
#if (CURRENT_OS == OSNAME_WINDOWS)

#ifndef PATH_H
#error Please use path.h instead.
#endif /* PATH_H */

#if (CURRENT_OS == OSNAME_WINDOWS)
#include <windef.h>
#include <winbase.h>
#include <shlobj.h>
#endif /* OSNAME_WINDOWS */

#ifdef __cplusplus
extern "C" {
#endif

int GetPathConfigDirectory_win32(UNICHAR *path, UNICHAR *folderName)
{
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, &path)) == 0)
    {
        /* Appends the name of the folder to the final path */
        _stringcopy(&path, folderName);
    }
    else
        return 1;

    return 0;
}

int GetPathAppDirectory_win32(UNICHAR *path)
{
    /* Returns the path where the program itself is located in */
    return ((GetModuleFileName(NULL, &path, MAX_PATH) == ERROR_SUCCESS) ? 0 : 1);
}

int GetPathTempDirectory_win32(UNICHAR *path)
{
    /* Grabs the path where the temporary files are */
    return ((GetTempPath(MAX_PATH, &path) == 0) ? 1 : 0);
}

#ifdef __cplusplus
}
#endif

#endif /* OSNAME_WINDOWS */
#endif /* PATH_WIN32_H */
