// This file is public domain software.
#include <windows.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return -1;
    HWND hwnd = (HWND)strtol(argv[1], NULL, 0);
    printf("IsWindowVisible: %d\n", IsWindowVisible(hwnd));
    return 0;
}
