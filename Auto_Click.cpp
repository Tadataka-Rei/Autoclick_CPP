#include <iostream>
#include <Windows.h>

bool bState{false};

void menu(bool bState)
{

    system("cls");

    std::cout << "autoclicker v1.0\n";

    if (bState)
    {
        std::cout << "Status: ON\n";
    }
    else
    {
        std::cout << "Status: OFF\n";
    }
}

void Click(int wait)
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(wait);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(wait);
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nWinMode)
{
    static const TCHAR szAppName[] = TEXT("MinimalWindowsApp");

    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    wc.hIconSm = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    wc.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;

    // neu tao clas window bi loi
    if (0 == RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Can't Register the Window Class!"), szAppName, MB_OK | MB_ICONERROR);
        return E_FAIL;
    }

    // title
    static const TCHAR szAppTitle[] = TEXT("Auto_Clicker_1.0");

    // create the window
    HWND hwnd = CreateWindow(szAppName, szAppTitle,
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             NULL, NULL, hInstance, NULL);

    if (NULL == hwnd)
    {
        MessageBox(NULL, TEXT("Unable to Create the Main Window!"), szAppName, MB_OK | MB_ICONERROR);
        return E_FAIL;
    }

    // update va show window
    ShowWindow(hwnd, nWinMode);
    UpdateWindow(hwnd);

    static BOOL bRet;
    static MSG msg;

    // vong lap chinh
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) // 0 = WM_QUIT
    {
        if (-1 == bRet)
        {
            MessageBox(NULL, TEXT("Unable to Continue!"), szAppName, MB_OK | MB_ICONERROR);
            return E_FAIL;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        HDC hdc;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);

        // draw some text in the client area
        RECT rect;
        GetClientRect(hwnd, &rect);
        DrawText(hdc, TEXT("CLICK!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        EndPaint(hwnd, &ps);
        return S_OK;

    case WM_DESTROY:
        // EXIT
        PostQuitMessage(0);
        return S_OK;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
