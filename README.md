# Lee's Game Development Library #

This library is designed to provide support for cross-platform game development across several desktop platforms (e.g. Windows, GNU/Linux, BSD, etc.) in a compact and lightweight fashion. However, it is currently not designed to be a complete replacement to existing multimedia libraries (e.g. [SDL](https://www.libsdl.org/), [SFML](https://www.sfml-dev.org/), etc.).

## Note for Windows Developers ##

This library is currently designed to be able to run comfortably in Windows XP or later. Although this version is now considered to be deprecated by most people, the open source development of [ReactOS](http://reactos.org/) has, for the moment, kept that support still alive. However, if the kernel target of ReactOS should switch to a later version of Windows (e.g. Windows 7), the target may also change.

## Building ##

Compiling this library should be easy since all you have to do is just drop the headers into your project and compile. However, if you want to compile in Windows under GCC, then [Mingw-w64](https://mingw-w64.org/) is recommended as it provides better support than [MinGW](https://osdn.net/projects/mingw/). It should also be able to be built under MinGW, but this hasn't yet been tested yet.

### Windows Dependencies ###

* shell32
* advapi32
* kernel32

## Disclaimer ##

This project is the result of experimentation with cross-platform code as a side hobby. Not all of it has been formally tested in an actual development enviornment, so make sure you test it before you actually use it. Also, if you find any bugs or want to provide any enhancements, don't hesitate to do a pull request. I'm not too picky, and as long as it works, I'll most likely pull it.

## License ##

The code is licensed under a Modified BSD License.
