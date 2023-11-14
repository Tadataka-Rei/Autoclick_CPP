#pragma once

#include <windows.h>

class SettingWindow
{
public:
    SettingWindow(HINSTANCE hInstance);
    void Show();

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HWND hwnd;
};
