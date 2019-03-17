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

#if !defined(_WIN32) && defined(UNICODE)
#warning ("POSIX-based systems doesn't have any support for UNICODE. Setting to ANSI output.")
#undef UNICODE
#endif

#ifdef UNICODE
typedef wchar_t UNICHAR;
#define _T(x) L##x
#define fileopen _wfopen
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
#define fileopen fopen
#define stringlength strlen
#define stringcopy strcpy
#define stringcat strcat
#define stringncompare strncmp
#define stringcompare strcmp
#define findstring strchr
#define stringspan strcspn
#define currenttime asctime
#endif /* UNICODE */

#ifdef(_WIN32)
typedef HANDLE APP_INSTANCE;
#else
typedef unsigned __int64 DWORDLONG;
typedef sem_t* APP_INSTANCE;
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

/* Used to make reading source code used to determine the 
   OS type when compiling easy */
#if defined(__linux__) || defined(__gnu_linux__)
#define OSTYPE_LINUX
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || \
      defined(__NetBSD__) || defined(__bsdi__) || \
      defined(__DragonFly__)
#define OSTYPE_BSD
#elif defined(__APPLE__) && defined(__MACH__)
#define OSTYPE_OSX
#elif defined(OS2) || defined(_OS2)
#define OSTYPE_OS2
#else
#error Compile level of OS detection is not defined!
#endif

#ifdef __cplusplus
}
#endif

#endif /* SHARED_H */
