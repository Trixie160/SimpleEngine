#include <cassert>
#include "engine.h"

Engine::Engine()
	: myHWND(nullptr)
	, myGraphicsEngine(nullptr)
{
}

Engine::~Engine()
{
	if (myHWND != nullptr)
		delete myHWND;

	if (myGraphicsEngine != nullptr)
		delete myGraphicsEngine;

	myHWND = nullptr;
	myGraphicsEngine = nullptr;
}

void Engine::Init(HINSTANCE& hInstance, const int aWidth, const int aHeight)
{
	myHWND = SetupMainWindow(hInstance, aWidth, aHeight);
	assert(myHWND && "Failed To Create Window");

	ShowWindow(*myHWND, 1);
	UpdateWindow(*myHWND);

	myGraphicsEngine = new GraphicsEngine();
	myGraphicsEngine->Init(aHeight, aWidth, *myHWND);
}

HWND* Engine::SetupMainWindow(HINSTANCE& hInstance, const int aWidth, const int aHeight)
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
	assert(wcex.hIcon != NULL && "Failed to load icon");

	if (!RegisterClassExW(&wcex))
	{
		MessageBox(NULL, L"Failed to register window class", L"Error", MB_ICONERROR);
		return nullptr;
	}

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

bool Engine::BeginFrame()
{
	return myGraphicsEngine->BeginFrame();
}

void Engine::Render()
{
	myGraphicsEngine->Render();
}

