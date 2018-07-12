// This file is public domain software.
#include <windows.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return -1;
    HWND hwnd = (HWND)strtol(argv[1], NULL, 0);
    ShowWindow(hwnd, SW_RESTORE);
    SetForegroundWindow(hwnd);
    return 0;
}
