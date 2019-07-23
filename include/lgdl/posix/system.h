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
#ifndef SYSTEM_POSIX_H
#define SYSTEM_POSIX_H

#include <sys/utsname.h>

#ifndef SYSTEM_H
#error Please use system.h instead.
#endif /* SYSTEM_H */

#ifdef __cplusplus
extern "C" {
#endif

int GetSystemOsName_posix(UNICHAR *osName)
{
    struct utsname unameData;

    /* Try to grab the name of the operating system the computer
       the user is currently using. */
    uname(&unameData);
    if (unameData == 0)
    {
        /* Grabs the name of the operating system and version
           so it can better help with debugging. */
        /* Linux x.x.xx (xx) */
        _stringcopy(osName, unameData.sysname);
        _stringcat(osName, " ");
        _stringcat(osName, unameData.release);
        _stringcat(osName, " (");
        _stringcat(osName, unameData.version);
        _stringcat(osName, " )");
    }
    else
    {
        /* If uname doesn't work, then at least try to get the
           name of the operating system. */
#if (CURRENT_OS == OSNAME_LINUX)
        _stringcopy(osName, _T("GNU/Linux"));
#elif (CURRENT_OS == OSNAME_HURD)
        _stringcopy(osName, _T("GNU/Hurd"));
#elif (CURRENT_OS == OSNAME_BSD)
        _stringcopy(osName, _T("BSD"));
#elif (CURRENT_OS == OSTYPE_OSX)
        _stringcopy(osName, _T("macOS"));
#else
        _stringcopy(osName, _T("POSIX-based OS"));
#endif
    }

    /* Return the operating system type */
#if (CURRENT_OS == OSNAME_LINUX)
    return OSNAME_LINUX;
#elif (CURRENT_OS == OSNAME_BSD)
    return OSNAME_BSD;
#elif (CURRENT_OS == OSNAME_MACOS)
    return OSNAME_MACOS;
#elif (CURRENT_OS == OSNAME_HURD)
    return OSNAME_HURD;
#endif
    return OSNAME_NONE;
}

int GetSystemAppName_posix(char *appName)
{
#if (CURRENT_OS == OSNAME_BSD) || \
    (CURRENT_OS == OSNAME_MACOS)
    /* Both BSD and OSX use this method */
    _stringcopy(appName, getprogname());
    return ((appName == NULL) ? 1 : 0);
#elif (CURRENT_OS == OSNAME_LINUX)
    extern char *program_invocation_short_name;
    return ((_stringcopy(appName, program_invocation_short_name) == NULL) ? 1 : 0);
#endif

    return 1;
}

DWORDLONG GetSystemTotalMemory_posix(void)
{
    long mb_count, page_size;
    DWORDLONG mb;

    /* Count the number of physical pages */
    mb_count = sysconf(_SC_PHYS_PAGES);
    if (mb_count == -1)
        return 0;

    /* Counts the page size */
    page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1)
        return 0;

    /* Calculate the total system memory into something more consistent */
    mb = (DWORDLONG)((double)mb_count * (double)page_size / (1024 * 1024));

    /* Round up to the nearest 16Mb */
    mb = (mb + 8) & ~15;

    return (DWORDLONG)mb;
}

APP_INSTANCE CreateAppInstance_posix(char *instance_name)
{
    sem_t *testSem;

    /* Try to create an instance */
    testSem = sem_open(instance_name, O_CREAT | O_EXCL);

    /* Check to see if there is another instance of the program running */
    if ((testSem == SEM_FAILED) && (errno == EEXIST))
        return NULL;

    return testSem;
}

void DestroyAppInstance_posix(char *instance_name, APP_INSTANCE instance)
{
    /* Remove the application instance once it's done so it can be 
       used later on */
    sem_unlink(instance_name);
    sem_close(instance);
}

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_POSIX_H */
