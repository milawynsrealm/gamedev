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
#ifndef SYSTEM_POSIX_H
#define SYSTEM_POSIX_H

#ifndef SYSTEM_H
#error Please use system.h instead.
#endif /* SYSTEM_H */

#include <unistd.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

int GetSystemUserName_posix(WCHAR *userName)
{
    return (getlogin_r(&userName, LOGIN_NAME_MAX) == 0 ? 0 : 1);
}

int GetSystemComputerName_posix(WHCAR *compName)
{
    return (gethostname(&compName, HOST_NAME_MAX) == 0 ? 0 : 1);
}

DWORDLONG GetSystemTotalMemory_posix(void)
{
    long mb_count, page_size;
    DWORDLONG mb;

    mb_count = sysconf(_SC_PHYS_PAGES);
    if (mb_count == -1)
        return 0;

    page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1)
        return 0;

    mb = (DWORDLONG)((double)mb_count * (double)page_size / (1024 * 1024));

    /* Round up to the nearest 16Mb */
    mb = (mb + 8) & ~15;

    return (DWORDLONG)mb;
}

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_POSIX_H */
