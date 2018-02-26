/*
	Copyright (c) 2018, Lee Schroeder
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

#ifdef(_WIN32)
#include "win32/system.h"
#else
#include "posix/system.h"
#endif /* _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

/* Grabs the Operating System's name */
int GetSystemOsName(UNICHAR *osName)
{
#if defined(_WIN32)
    return GetSystemOsName_win32(&osName);
#elif defined(__linux__) || defined(__gnu_linux__)
    strcpy(osName, "GNU/Linux");
    return OSNAME_LINUX
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || \
  defined(__NetBSD__) || defined(__bsdi__) || \
  defined(__DragonFly__)
    strcpy(osName, "BSD");
    return OSNAME_BSD;
#elif defined(__APPLE__) && defined(__MACH__)
    strcpy(osName, "macOS");
    return OSNAME_MACOS;
#elif defined(__ANDROID__)
    strcpy(osName, "Android");
    return OSNAME_ANDROID;
#elif defined(__BEOS__)
    strcpy(osName, "BeOS");
    return OSNAME_BEOS;
#elif defined(OS2) || defined(_OS2)
    strcpy(osName, "OS/2");
    return OSNAME_OS2;
#else
    strcpy(osName, "Unknown");
    return OSNAME_NONE;
#endif
}

/* Grabs the type of system architecture the
   program is running on */
int GetSystemArchitecture(void)
{
#if defined(__i386) || defined(_M_IX86)
    return ARCH_86;
#elif defined(__amd64__) || defined(_M_X64)
    return ARCH_AMD64;
#elif defined(__ia64__) || defined(_M_IA64)
    return ARCH_ITANIUM;
#elif defined(__arm__) || defined(_M_ARM)
    return ARCH_ARM;
#elif defined(__alpha__) || defined(_M_ALPHA)
    return ARCH_ALPHA;
#elif defined(__powerpc) || defined(_M_PPC)
    return ARCH_PPC;
#else
    return ARCH_NONE;
#endif /* __i386 */
}

/* Determines what the user's name is */
int GetSystemUserName(UNICHAR *userName)
{
#if defined(_WIN32)
    return GetSystemUserName_win32(&userName);
#else
    return GetSystemUserName_posix(&userName);
#endif /* _WIN32 */
}

/* Grabs the name of the computer */
int GetSystemComputerName(UNICHAR *compName)
{
#if defined(_WIN32)
    return GetSystemComputerName_win32(&compName);
#else
    return GetSystemComputerName_posix(&compName);
#endif /* _WIN32 */
}

/* Determines how much system memory is 
   available overall */
DWORDLONG GetSystemTotalMemory(void)
{
#if defined(_WIN32)
    return GetSystemTotalMemory_win32();
#else
    return GetSystemTotalMemory_posix();
#endif /* _WIN32 */
}

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_H */
