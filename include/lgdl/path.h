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
#ifndef PATH_H
#define PATH_H

#include "shared.h"

#ifdef(_WIN32)
#include "win32/path.h"
#else
#include "posix/path.h"
#endif /* _WIN32 */

WCHAR *GetPathDirSeperator(void)
{
#ifdef(_WIN32)
    return L'\\';
#else
    return '/';
#endif /* _WIN32 */
}

int GetPathHomeDirectory(WCHAR *path)
{
#ifdef(_WIN32)
    return GetPathHomeDirectory_win32(&path);
#else
    return GetPathHomeDirectory_posix(&path);
#endif /* _WIN32 */
}

int GetPathAppDirectory(WCHAR *path)
{
#ifdef(_WIN32)
    return GetPathAppDirectory_win32(&path);
#else
    return GetPathAppDirectory_posix(&path);
#endif /* _WIN32 */
}

int GetPathTempDirectory(WCHAR *path)
{
#ifdef(_WIN32)
    return GetPathTempDirectory_win32(&path);
#else
    return GetPathTempDirectory_posix(&path);
#endif /* _WIN32 */
}

#endif /* PATH_H */