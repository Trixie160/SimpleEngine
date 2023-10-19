#pragma once
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class Engine
{
public:
    Engine();
    ~Engine();

    void Init(HINSTANCE hInstance, const int aWidth, const int aHeight);
private:
    HWND* SetupMainWindow(HINSTANCE hInstance, const int aWidth, const int aHeight);
private:
    HWND* myHWND;
};
