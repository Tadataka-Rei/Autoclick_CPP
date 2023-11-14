#pragma once

#include <windows.h>
class Clicker
{
public:
    bool Auto{false};
    void CALLBACK click(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
};