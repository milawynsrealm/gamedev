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
#ifndef PATH_POSIX_H
#ifndef PATH_POSIX_H
#ifndef(_WIN32)

#ifndef PATH_H
#error Please use path.h instead.
#endif /* PATH_H */

#include <string.h>
#include <unistd.h>
#include <pwd.h>

int GetPathHomeDirectory_posix(WCHAR *path)
{
    struct passwd *p;

    /* Attempts to get the home directory for the current user */
    p = getpwnam(getlogin());

    /* If the first attempt fails, try to use the environment
       variable as a method of last resort */
    if (p != NULL)
        strcpy(&path, p->pw_dir);
    else
        strcpy(&path, getenv("HOME"));

    /* If the length of the string is nothing, assume failure */
    return strlen(&path) == 0 ? 1 : 0;
}

int GetPathAppDirectory_posix(WCHAR *path)
{
    return (((readlink("/proc/self/exe", &path, MAX_PATH)) == -1) ? 1 : 0);
}

int GetPathTempDirectory_posix(WCHAR *path)
{
    strcpy(&path, "/tmp");
    return 0;
}

#endif /* _WIN32 */
#endif /* PATH_POSIX_H */
