#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11Buffer;

class Camera;
class Triangle;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init(int aHeight, int aWidth, HWND& aWindowHandle);
	bool BeginFrame();

	void Render();
	void Test();
private:
	ComPtr<ID3D11Device> myDevice;
	ComPtr<ID3D11DeviceContext> myContext;
	ComPtr<IDXGISwapChain> mySwapChain;
	ComPtr<ID3D11RenderTargetView> myBackBuffer;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;
	
	Camera* myCamera;
	Triangle* myTriangle;

	float myColor[4];
};