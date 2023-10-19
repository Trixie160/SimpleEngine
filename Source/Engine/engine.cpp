#include <cassert>
#include "engine.h"

Engine::Engine()
	: myHWND(nullptr)
{
}

Engine::~Engine()
{
	if (myHWND != nullptr)
		delete myHWND;

	myHWND = nullptr;
}

void Engine::Init(HINSTANCE hInstance, const int aWidth, const int aHeight)
{
	myHWND = SetupMainWindow(hInstance, aWidth, aHeight);
	assert(myHWND && "Failed To Create Window");

	ShowWindow(*myHWND, 1);
	UpdateWindow(*myHWND);
}

HWND* Engine::SetupMainWindow(HINSTANCE hInstance, const int aWidth, const int aHeight)
{
	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszClassName = L"Natdanai";
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));

	RegisterClassExW(&wcex);

	HWND* hwnd = new HWND;
	*hwnd = CreateWindow(
		L"Natdanai",
		L"SimpleEngine",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		aWidth,
		aHeight,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return hwnd;
}
