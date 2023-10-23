#pragma once
#include "Model/Model.h"
#include "Shaders/Shader.h"

using Microsoft::WRL::ComPtr;

class Camera;
class Triangle;

struct FrameBufferData
{
	SimpleUtilities::Matrix4x4f worldToClipMatrix;
};

struct ObjectBufferData
{
	SimpleUtilities::Matrix4x4f modelToWorldMatrix;
};

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init(const int aHeight, const int aWidth, HWND& aWindowHandle);
	bool BeginFrame();

	void Render();
	void Draw(Model& aModel, Shader& aShader);
	void Test();
private:
	void CreateViewport(const int aHeight, const int aWidth);
	bool CreateSwapChain(HWND& aWindowHandle, const int aHeight, const int aWidth);
	bool CreateBackBuffer();
	bool CreateFrameBuffer();
private:
	ComPtr<ID3D11Device> myDevice;
	ComPtr<ID3D11DeviceContext> myContext;
	ComPtr<IDXGISwapChain> mySwapChain;

	ComPtr<ID3D11RenderTargetView> myBackBuffer;
	ComPtr<ID3D11DepthStencilView> myDepthBuffer;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;
	
	Camera* myCamera;
	Triangle* myTriangle;

	float myColor[4];
};