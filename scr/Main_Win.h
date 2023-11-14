#pragma once

#include <windows.h>
#include "SettingWindow.h"

class MainWindow
{
public:
    MainWindow(HINSTANCE hInstance, const char *title, int nCmdShow);
    void Run();

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HWND hwnd;
    static SettingWindow settingWin;
};
