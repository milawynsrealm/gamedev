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
#ifndef SYSTEM_H
#define SYSTEM_H

#include "shared.h"

#if (CURRENT_OS == OSNAME_WINDOWS)
#include <windef.h>
#include <winbase.h>
#include <winreg.h>
#include <winuser.h>
#include "win32/system.h"
#else
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "posix/system.h"
#endif /* OSNAME_WINDOWS */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if (CURRENT_OS == OSNAME_WINDOWS)
typedef HWND LgdlWndHandle;
#elif (CURRENT_OS == OSTYPE_LINUX) || (CURRENT_OS == OSTYPE_BSD)
typedef Window LgdlWndHandle;
#else /* OSTYPE_OSX or misc. */
typedef void* LgdlWndHandle;
#endif /* OSNAME_WINDOWS */

int FlashSystemWindow(LgdlWndHandle wndHandle)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return (FlashWindow(wndHandle, TRUE) ? 0 : 1);
#endif /* OSNAME_WINDOWS */
    return 0;
}

int GetCompilerName(UNICHAR *compileName)
{
#if defined(__BORLANDC__)
    _stringcopy(compileName, _T("Borland C++ "));
    _stringcat(compileName, _inttostr(__BORLANDC__));
#elif defined(__clang__)
    _stringcopy(compileName, _T("Clang "));
    _stringcat(compileName, _inttostr(__clang_major__));
    _stringcat(compileName, _T("."));
    _stringcat(compileName, _inttostr(__clang_minor__));
#elif defined(__DMC__)
    _stringcopy(compileName, _T("Digital Mars "));
    _stringcat(compileName, _inttostr(__DMC__));
#elif defined(__GNUC__)
    _stringcopy(compileName, _T("GNU GCC C/C++ "));
    _stringcat(compileName, _inttostr(__GNUC__));
    _stringcat(compileName, _T("."));
    _stringcat(compileName, _inttostr(__GNUC_MINOR__));
#elif defined(_MSC_VER)
    _stringcopy(compileName, _T("Microsoft Visual C/C++ "));
    _stringcat(compileName, _inttostr(_MSC_VER));
#else
    _stringcopy(compileName, _T("Unknown Compiler"));
#endif
    return 0;
}

/* Grabs the Operating System's name */
int GetSystemOsName(UNICHAR *osName)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return GetSystemOsName_win32(osName);
#elif (CURRENT_OS == OSTYPE_LINUX) || \
      (CURRENT_OS == OSTYPE_BSD) || \
      (CURRENT_OS == OSTYPE_OSX)
    return GetSystemOsName_posix(osName);
#elif (CURRENT_OS == OSNAME_ANDROID)
    _stringcopy(osName, "Android");
    return OSNAME_ANDROID;
#elif (CURRENT_OS == OSNAME_BEOS)
    _stringcopy(osName, "BeOS");
    return OSNAME_BEOS;
#elif defined(CURRENT_OS == OSTYPE_OS2)
    _stringcopy(osName, "OS/2");
    return OSNAME_OS2;
#else
    _stringcopy(osName, "Unknown");
    return OSNAME_NONE;
#endif
}

int GetSystemAppName(UNICHAR *appName)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return ((GetModuleFileName(NULL, appName, MAX_PATH) == 0) ? 1 : 0);
#else
    return GetSystemAppName_posix(&appName);
#endif
}

/* Grabs the type of system architecture the
   program is running on */
int GetSystemArchitecture(void)
{
    return CURRENT_ARCH;
}

/* Determines what the user's name is */
int GetSystemUserName(UNICHAR *userName)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    DWORD uNameSize = 256;

    return GetUserName(userName, &uNameSize+1);
#else
    return ((getlogin_r(userName, LOGIN_NAME_MAX) == 0) ? 0 : 1);
#endif /* _WIN32 */
}

/* Grabs the name of the computer */
int GetSystemComputerName(UNICHAR *compName)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    DWORD compNameSize = 32767;

    return GetComputerName(compName, &compNameSize);
#else
    return ((gethostname(compName, HOST_NAME_MAX)) == 0 ? 0 : 1);
#endif /* _WIN32 */
    return 0;
}

/* Determines how much system memory is 
   available overall */
DWORDLONG GetSystemTotalMemory(void)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return GetSystemTotalMemory_win32();
#else
    return GetSystemTotalMemory_posix();
#endif /* _WIN32 */
    return 0;
}

/* Make sure the system is a certain version or later. 
   For now, this only works with Windows. */
int IsMinimumOS(int version)
{
#if (CURRENT_OS == OSNAME_WINDOWS)
    return IsMinimumOS_win32(version);
#endif
    return 0;
}

APP_INSTANCE CreateAppInstance(UNICHAR *instance_name)
{
    /* A name is needed to be successful */
    if (instance_name == NULL)
        return NULL;

#if (CURRENT_OS == OSNAME_WINDOWS)
    return CreateAppInstance_win32(instance_name);
#else
    return CreateAppInstance_posix(instance_name);
#endif /* _WIN32 */
    return NULL;
}

int DestroyAppInstance(char *instance_name, APP_INSTANCE instance)
{
    /* Make sure there's something to work with */
    if (instance == NULL)
        return 1;

#if (CURRENT_OS == OSNAME_WINDOWS)
    DestroyAppInstance_win32(instance);
#else
    /* Make sure there's an instance name to work with since 
       POSIX-based systems need it for reference */
    if (instance_name == NULL)
        return 1;

    DestroyAppInstance_posix(&instance_name, instance);
#endif /* _WIN32 */
    return 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTEM_H */
