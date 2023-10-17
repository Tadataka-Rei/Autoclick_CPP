#include <iostream>
#include <Windows.h>

bool bState{false};
bool Auto{false};

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

void CALLBACK click(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
    if (Auto)
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

        Sleep(100);

        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nWinMode)
{
    static const TCHAR szAppName[] = TEXT("MinimalWindowsApp");

    WNDCLASSEX wc;
    HWND hwnd;
    MSG messages;

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

    // check if cant create window class
    if (0 == RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Can't Register the Window Class!"), szAppName, MB_OK | MB_ICONERROR);
        return E_FAIL;
    }
    // title
    static const TCHAR szAppTitle[] = TEXT("Auto_Clicker_1.0");

    // create the window
    hwnd = CreateWindow(szAppName, szAppTitle,
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
    while (GetMessage(&messages, NULL, 0, 0))
    {
        // Translate virtual-key messages into character messages
        TranslateMessage(&messages);
        // Send message to WindowProcedure
        DispatchMessage(&messages);
    }

    // The program return-value is 0 - The value that PostQuitMessage() gave
    return messages.wParam;
    UpdateWindow(hwnd);

    static BOOL bRet;
    static MSG msg;

    // main loop
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

        SetTimer(NULL, 0, 1000 * 3, (TIMERPROC)&click);

        if (GetAsyncKeyState(VK_LCONTROL))
        {
            Auto = !Auto;

            Sleep(500);
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

        // draw some text
        RECT rect;
        GetClientRect(hwnd, &rect);
        DrawText(hdc, TEXT("CLICK!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 3:
            PostQuitMessage(0);
            break;
        case 1:
            MessageBox(hwnd, TEXT("Click button clicked!"), TEXT("Button Clicked"), MB_OK);
            break;
        case 2:
            MessageBox(hwnd, TEXT("Back button clicked!"), TEXT("Button Clicked"), MB_OK);
            break;
        }
        break;
    case WM_CREATE:
    {
        HMENU hMenu, hSubMenu;
        hMenu = CreateMenu();
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, 1, TEXT("Click"));
        AppendMenu(hSubMenu, MF_STRING, 2, TEXT("Setting"));
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, TEXT("UI"));
        AppendMenu(hMenu, MF_STRING, 3, TEXT("Exit"));

        // Set the menu to the window
        SetMenu(hwnd, hMenu);
        break;
    }
    case WM_DESTROY:
        // EXIT
        PostQuitMessage(0);
        return S_OK;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}