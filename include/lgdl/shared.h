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
#ifndef SHARED_H
#define SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

#define OSTYPE_LINUX   0
#define OSTYPE_BSD     1
#define OSTYPE_OSX     2
#define OSTYPE_OS2     3
#define OSTYPE_WINDOWS 4
#define OSTYPE_ANDROID 5
#define OSTYPE_BEOS    6
#define OSTYPE_NONE    7

/* Used to make reading source code used to determine the
   OS type when compiling easy */
#if defined(__linux__) || defined(__gnu_linux__)
#define CURRENT_OS OSTYPE_LINUX
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || \
      defined(__NetBSD__) || defined(__bsdi__) || \
      defined(__DragonFly__)
#define CURRENT_OS OSTYPE_BSD
#elif defined(__APPLE__) && defined(__MACH__)
#define CURRENT_OS OSTYPE_OSX
#elif defined(OS2) || defined(_OS2)
#define CURRENT_OS OSTYPE_OS2
#elif defined(_WIN32)
#define CURRENT_OS OSTYPE_WINDOWS
#elif defined(__ANDROID__)
#define CURRENT_OS OSTYPE_ANDROID
#elif defined(__BEOS__)
#define CURRENT_OS OSTYPE_BEOS
#else
#define CURRENT_OS OSTYPE_NONE
#endif

#ifdef UNICODE
typedef wchar_t UNICHAR;
#define _T(x) L##x
#define fileputs fputws
#define fileopen _wfopen
#define consoleprint printf
#define stringlength wcslen
#define stringcopy wcscpy
#define stringcat wcscat
#define stringncompare wcsncmp
#define stringcompare wcscmp
#define findstring wcschr
#define stringspan wcscspn
#define currenttime _wasctime

#else /* ANSI */
typedef char UNICHAR;
#define _T(x) x
#define fileputs fputs
#define fileopen fopen
#define consoleprint wprintf
#define stringlength strlen
#define stringcopy strcpy
#define stringcat strcat
#define stringncompare strncmp
#define stringcompare strcmp
#define findstring strchr
#define stringspan strcspn
#define currenttime asctime
#endif /* UNICODE */

#if (CURRENT_OS == OSTYPE_WINDOWS)
typedef HANDLE APP_INSTANCE;
#else
typedef unsigned __int64 DWORDLONG;
typedef sem_t* APP_INSTANCE;
#endif /* OSNAME_WINDOWS */

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

/* Used to derermine the minimum version of Windows */
#define MINOS_NONE  0
#define MINOS_XP    1
#define MINOS_VISTA 2
#define MINOS_7     3
#define MINOS_8     4

/* Determines the current system architecture */
#if defined(__i386) || defined(_M_IX86)
#define CURRENT_ARCH ARCH_86;
#elif defined(__amd64__) || defined(_M_X64)
#define CURRENT_ARCH ARCH_AMD64;
#elif defined(__ia64__) || defined(_M_IA64)
#define CURRENT_ARCH ARCH_ITANIUM;
#elif defined(__arm__) || defined(_M_ARM)
#define CURRENT_ARCH ARCH_ARM;
#elif defined(__alpha__) || defined(_M_ALPHA)
#define CURRENT_ARCH ARCH_ALPHA;
#elif defined(__powerpc) || defined(_M_PPC)
#define CURRENT_ARCH ARCH_PPC;
#else
#define CURRENT_ARCH ARCH_NONE;
#endif /* __i386 */

#ifdef __cplusplus
}
#endif

#endif /* SHARED_H */
