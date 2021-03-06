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
#ifndef PATH_POSIX_H
#define PATH_POSIX_H

#ifndef PATH_H
#error Please use path.h instead.
#endif /* PATH_H */

#include <string.h>
#include <unistd.h>
#include <pwd.h>

#ifdef __cplusplus
extern "C" {
#endif

int GetPathConfigDirectory_posix(UNICHAR *path, UNICHAR *folderName)
{
#if (CURRENT_OS == OSTYPE_OSX) /* macOS */
    _stringcopy(&path, getenv("HOME"));
    _stringcat(&path, "Library/Application Support/");
    _stringcat(&path, folderName);
#else /* GNU/Linux, BSD, etc. */
    _stringcopy(&path, getenv("XDG_CONFIG_HOME"));

    /* If XDG_CONFIG_HOME is not available, then use HOME as the 
       backup solution */
    if (_stringlength(&path) == 0)
    {
        /* /home/<user>/.local/share/ */
        if (_stringcopy(&path, getenv("HOME")) == NULL)
            return 1;

        _stringcat(&path, ".local/share/");
    }

    /* Add the folder name */
    if ((_stringlength(&path) != 0) && (folderName != NULL))
        _stringcat(&path, folderName);

#endif /* OSTYPE_OSX */

    /* If the length of the string is nothing, assume failure */
    return _stringlength(&path) == 0 ? 1 : 0;
}

int GetPathAppDirectory_posix(UNICHAR *path)
{
    /* Grabs the path of the program's location */
    return (((readlink("/proc/self/exe", &path, MAX_PATH)) == -1) ? 1 : 0);
}

int GetPathTempDirectory_posix(UNICHAR *path)
{
    /* Returns the location of the temp directory */
    return ((_stringcopy(&path, "/tmp") == NULL) ? 1 : 0);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PATH_POSIX_H */
