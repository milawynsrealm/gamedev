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
#ifdef(_WIN32)

#ifndef SYSTEM_H
#error Please use system.h instead.
#endif /* SYSTEM_H */

#include <windef.h>
#include <winbase.h>
#include <winreg.h>

#ifdef __cplusplus
extern "C" {
#endif

int GetSystemOsName_win32(UNICHAR *osName)
{
    HKEY hKey;
    LONG res = ERROR_SUCCESS;

    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
        res = RegQueryValueExW(hKey, L"ProductName", NULL, &dwType, (LPBYTE)osName, &dwSize);
        RegCloseKey(hKey);
    }

    /* If no name is found in the registry, then just use Windows */
    if ((res != ERROR_SUCCESS) || (wcslen(&osName) == 0))
        wcscpy(osName, L"Windows NT");

    return OSNAME_WINDOWS;
}

int GetSystemUserName_win32(UNICHAR *userName)
{
    return GetUserNameW(&userName, UNLEN+1);
}

int GetSystemComputerName_win32(UNICHAR *compName)
{
    return GetComputerNameW(&compName, 32767);
}

DWORDLONG GetSystemTotalMemory_win32(void)
{
    MEMORYSTATUSEX totalMem;

    totalMem.dwLength = sizeof(totalMem);
    GlobalMemoryStatusEx(&totalMem);

    /* Returns the total physical memory in kilobytes */
    return totalMem.ullTotalPhys / 1024;
}

int IsMinimumOS_win32(void)
{
    OSVERSIONINFOEX osInfo;

	ZeroMemory(&osInfo, sizeof(OSVERSIONINFO));
    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osInfo);

	/* Check to make sure that the program is running in Windows XP or later */
	if ((osInfo.dwMajorVersion < 5) ||
       ((osInfo.dwMajorVersion == 5) && (osInfo.dwMinorVersion >= 1)))
		return 0;

    return 1;
}

APP_INSTANCE CreateSingleAppInstance_win32(UNICHAR *instance_name)
{
    HANDLE checkInstance;
    checkInstance = CreateMutex(NULL, FALSE, instance_name);

    /* If there is already an instance of the program, then return null */
    if ((GetLastError() == ERROR_ALREADY_EXISTS)||(GetLastError() == ERROR_ACCESS_DENIED))
        return NULL;

    return checkInstance;
}

void DestroySingleAppInstance_win32(APP_INSTANCE instance)
{
    CloseHandle(instance);
}

#ifdef __cplusplus
}
#endif

#endif /* _WIN32 */
#endif /* SYSTEM_WIN32_H */
