#include <d3d11.h>
#include "GraphicsEngine.h"
#include <Windows.h>
#include "Triangle/Triangle.h"
#include "Camera/Camera.h"

//#define REPORT_DX_WARNINGS

struct FrameBufferData
{
	SimpleUtilities::Matrix4x4f worldToClipMatrix;
};

struct ObjectBufferData
{
	SimpleUtilities::Matrix4x4f modelToWorldMatrix;
};

GraphicsEngine::GraphicsEngine()
	: myTriangle(nullptr)
	, myCamera(new Camera)
	, myColor{ 0.0f, 0.25f, 0.50f, 1.0f }
{
}

GraphicsEngine::~GraphicsEngine()
{
	if (myCamera != nullptr)
		delete myCamera;

	if (myTriangle != nullptr)
		delete myTriangle;

	myCamera = nullptr;
	myTriangle = nullptr;
}

bool GraphicsEngine::Init(int aHeight, int aWidth, HWND& aWindowHandle)
{
	HRESULT result;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = aWidth;
	swapChainDesc.BufferDesc.Height = aHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = aWindowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	UINT creationFlags = 0;

#if defined (REPORT_DX_WARNINGS)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mySwapChain,
		&myDevice,
		nullptr,
		&myContext
	);

	ID3D11Texture2D* backBufferTexture;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
	if (FAILED(result))
	{
		return false;
	}

	result = myDevice->CreateRenderTargetView(backBufferTexture, nullptr, &myBackBuffer);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC textureDesc;
	backBufferTexture->GetDesc(&textureDesc);
	backBufferTexture->Release();

	myContext->OMSetRenderTargets(1, myBackBuffer.GetAddressOf(), nullptr);

	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float> (textureDesc.Width);
	viewport.Height = static_cast<float> (textureDesc.Height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	myContext->RSSetViewports(1, &viewport);

	myTriangle = new Triangle;
	if (!myTriangle->Init(myDevice.Get()))
		return false;


	{ //Test trying to Render 3D Triangle & Cube
		D3D11_BUFFER_DESC bufferDescription = { 0 };
		bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDescription.ByteWidth = sizeof(FrameBufferData);

		result = myDevice->CreateBuffer(&bufferDescription, nullptr, &myFrameBuffer);

		if (FAILED(result))
			return false;

		bufferDescription.ByteWidth = sizeof(ObjectBufferData);

		result = myDevice->CreateBuffer(&bufferDescription, nullptr, &myObjectBuffer);

		if (FAILED(result))
			return false;
	}

	return true;
}

bool GraphicsEngine::BeginFrame()
{
	MSG msg = { 0 };

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
			return false;
	}

	return true;
}

void GraphicsEngine::Render()
{
	myContext->ClearRenderTargetView(myBackBuffer.Get(), myColor);

	myTriangle->Render(myContext.Get());

	Test(); //Trying to draw 3D Cube & Triangle

	mySwapChain->Present(1, 0);
}

void GraphicsEngine::Test()
{
	{
		FrameBufferData frameBufferData = {};
		frameBufferData.worldToClipMatrix = myCamera->WorldToClipmatrix(myCamera->GetModelToWorldMatrix());
		D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
		myContext->Map(myFrameBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);
		memcpy(mappedBuffer.pData, &frameBufferData, sizeof(FrameBufferData));
		myContext->Unmap(myFrameBuffer.Get(), 0);
		myContext->VSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
	}

	{
		ObjectBufferData objectBufferData = {};
		objectBufferData.modelToWorldMatrix = SimpleUtilities::Matrix4x4f();
		D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
		myContext->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);
		memcpy(mappedBuffer.pData, &objectBufferData, sizeof(ObjectBufferData));
		myContext->Unmap(myObjectBuffer.Get(), 0);
		myContext->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
	}

}
