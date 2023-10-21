#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;

class Triangle;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init(int aHeight, int aWidth, HWND& aWindowHandle);
	bool BeginFrame();

	void Render();
private:
	ComPtr<ID3D11Device> myDevice;
	ComPtr<ID3D11DeviceContext> myContext;
	ComPtr<IDXGISwapChain> mySwapChain;
	ComPtr<ID3D11RenderTargetView> myBackBuffer;

	Triangle* myTriangle;
};