#include <lgdl/main.h>

int GuiMain(int argc, UNICHAR *argv[])
{
#ifdef(_WIN32)
    MessageBox(NULL, _T("This program is running well!"), _T("GuiMain Test Message"), MB_OK | MB_ICONINFORMATION);
#else /* POSIX */
    printf("GuiMain(): This Program is running well!\n");
#endif /* _WIN32 */
    return 0;
}
