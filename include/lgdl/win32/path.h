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
#ifndef PATH_WIN32_H
#ifndef PATH_WIN32_H
#ifdef(_WIN32)

#ifndef PATH_H
#error Please use path.h instead.
#endif /* PATH_H */

int GetPathHomeDirectory_win32(WCHAR *path)
{
    return (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, &path)) ? 0 : 1);
}

int GetPathAppDirectory_win32(WCHAR *path)
{
    return ((GetModuleFileNameW(NULL, &path, MAX_PATH) == ERROR_SUCCESS) ? 0 : 1);
}

int GetPathTempDirectory_win32(WCHAR *path)
{
    return ((GetTempPathW(MAX_PATH, &path) == 0) ? 1 : 0);
}
#endif /* _WIN32 */
#endif /* PATH_WIN32_H */