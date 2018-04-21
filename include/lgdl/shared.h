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
#ifndef SHARED_H
#define SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef(_WIN32)
typedef wchar_t UNICHAR;
typedef HANDLE APP_INSTANCE;

#define fileopen _wfopen
#define stringlength wcslen

#define _T(x) L##x
#else
typedef char UNICHAR;
typedef unsigned __int64 DWORDLONG;
typedef sem_t* APP_INSTANCE;

#define fileopen fopen
#define stringlength strlen

#define _T(x) x
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

#ifdef __cplusplus
}
#endif

#endif /* SHARED_H */
