// This file is public domain software.
#include <windows.h>

int main(int argc, char **argv)
{
    BOOL bFlag = TRUE;
    if (argc < 2)
        return -1;
    if (argc >= 3)
    {
        bFlag = atoi(argv[2]);
    }
    HWND hwnd = (HWND)strtol(argv[1], NULL, 0);
    SwitchToThisWindow(hwnd, bFlag);
    return 0;
}
