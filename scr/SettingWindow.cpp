#include "SettingWindow.h"
SettingWindow::SettingWindow(HINSTANCE hInstance)
{
    LPWSTR className = TEXT("SettingWindowClass");
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = className;
    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(0, className, TEXT("Setting Site"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, NULL, hInstance, NULL);
}

void SettingWindow::Show()
{
    ShowWindow(hwnd, SW_SHOW);
}

LRESULT CALLBACK SettingWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 3) // Back button
        {
            ShowWindow(hwnd, SW_HIDE); // Hide the setting window
            // TODO: Show the main window
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}