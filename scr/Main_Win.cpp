#include "Main_Win.h"

MainWindow::MainWindow(HINSTANCE hInstance, const char *title, int nCmdShow)
{
    LPWSTR WIN_name = TEXT("MainWindowClass");
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = WIN_name;
    RegisterClassEx(&wc);

    int titleLength = MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
    LPWSTR wideTitle = new WCHAR[titleLength];
    MultiByteToWideChar(CP_UTF8, 0, title, -1, wideTitle, titleLength);

    hwnd = CreateWindowEx(0, WIN_name, wideTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    delete[] wideTitle;
}

void MainWindow::Run()
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK MainWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) // Start button
        {
            MessageBox(hwnd, L"Start button pressed!", L"Button Pressed", MB_OK);
        }
        else if (LOWORD(wParam) == 2) // Setting button
        {
            ShowWindow(hwnd, SW_HIDE); // Hide the main window
            settingWin.Show();         // Show the setting window
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