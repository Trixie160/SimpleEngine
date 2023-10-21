#pragma once
#include <Windows.h>

class Timer;
class GraphicsEngine;

class Engine
{
public:
	Engine();
	~Engine();

	void Init(HINSTANCE& hInstance, const int aWidth, const int aHeight);

	bool BeginFrame();
	void Render();
public:
	float GetDeltaTime() const;
private:
	HWND* SetupMainWindow(HINSTANCE& hInstance, const int aWidth, const int aHeight);
private:
	HWND* myHWND;
	GraphicsEngine* myGraphicsEngine;
	Timer* myTimer;
};
