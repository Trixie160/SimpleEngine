#include "Engine/engine.h"
#include "Engine/Console/Console.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int /*nCmdShow*/)
{
	Engine engine;
	engine.Init(hInstance, 1280, 720);

	Console console;
	console.Init();

	while (engine.BeginFrame())
	{
		engine.Render();
	}

	int* leaks = new int();
	leaks;

	return 0;
}
