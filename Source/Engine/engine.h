#pragma once
#include "Graphics/GraphicsEngine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class GraphicsEngine;

class Engine
{
public:
    Engine();
    ~Engine();

    void Init(HINSTANCE& hInstance, const int aWidth, const int aHeight);

    bool BeginFrame();
    void Render();
private:
    HWND* SetupMainWindow(HINSTANCE& hInstance, const int aWidth, const int aHeight);
private:
    HWND* myHWND;
    GraphicsEngine* myGraphicsEngine;
};
