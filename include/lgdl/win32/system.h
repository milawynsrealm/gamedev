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
#ifndef SYSTEM_WIN32_H
#define SYSTEM_WIN32_H

#ifndef SYSTEM_H
#error Please use system.h instead.
#endif /* SYSTEM_H */

#include <windef.h>
#include <winbase.h>
#include <winreg.h>

int GetSystemOsName_win32(WCHAR *osName)
{
    HKEY hKey;
    LONG res;

    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
        return 1;

    res = RegQueryValueExW(hKey, L"ProductName", NULL, &dwType, (LPBYTE)osName, &dwSize);
    RegCloseKey(hKey);

    /* If no name is found in the registry, then just use Windows */
    if (res != ERROR_SUCCESS)
        wcscpy(osName, L"Windows NT");

    return OSNAME_WINDOWS;
}

int GetSystemUserName_win32(WCHAR *userName)
{
    return GetUserName(&userName, UNLEN+1);
}

int GetSystemComputerName_win32(WHCAR *compName)
{
    return GetComputerName(&compName, 32767);
}

#endif /* SYSTEM_WIN32_H */
