// This file is public domain software.
#include "MWindowBase.hpp"

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        MWindowBase::CenterWindowDx(hwnd);
        break;
    case WM_COMMAND:
        EndDialog(hwnd, IDCANCEL);
        break;
    }
    return 0;
}

class MMainWnd : public MWindowBase
{
public:
    HINSTANCE   m_hInst;        // the instance handle

    MMainWnd(HINSTANCE hInst)
        : m_hInst(hInst)
    {
    }

    virtual ~MMainWnd()
    {
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        CenterWindowDx();
        PostMessage(hwnd, WM_COMMAND, 999, 0);
        return TRUE;
    }

    void OnDestroy(HWND hwnd)
    {
        ::PostQuitMessage(0);
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        TCHAR szText[32];
        StringCchPrintf(szText, _countof(szText), TEXT("%p"), hwnd);
        SetWindowText(hwnd, szText);

        DialogBox(m_hInst, MAKEINTRESOURCE(1), hwnd, DialogProc);
    }

    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        default:
            return DefaultProcDx();
        }
    }

    BOOL StartDx(INT nCmdShow)
    {
        if (!CreateWindowDx(NULL, NULL, WS_OVERLAPPEDWINDOW, 0, 0, 0, 500, 200))
        {
            MsgBoxDx(TEXT("failure of CreateWindow"), NULL, MB_ICONERROR);
            return FALSE;
        }

        ::ShowWindow(*this, nCmdShow);
        ::UpdateWindow(*this);

        return TRUE;
    }

    INT RunDx()
    {
        // message loop
        MSG msg;
        while (::GetMessage(&msg, NULL, 0, 0))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        return INT(msg.wParam);
    }
};

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    MMainWnd wnd(hInstance);
    if (wnd.StartDx(SW_SHOWNORMAL))
    {
        return wnd.RunDx();
    }
    return -1;
}
