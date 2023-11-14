#include "Click.h"

void Clicker::click(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
    if (Auto)
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

        Sleep(100);

        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
}