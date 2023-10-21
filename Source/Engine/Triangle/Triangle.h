#pragma once
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

struct TimeBufferType
{
	float elapsedTime;
	float padding[3];
};

class Triangle
{
public:
	Triangle();
	~Triangle();

	bool Init(ID3D11Device* aDevice);
	void Render(ID3D11DeviceContext* aContext);
private:
	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;
	ComPtr<ID3D11Buffer> myTimeBuffer;

	ComPtr<ID3D11VertexShader> myVertexShader;
	ComPtr<ID3D11PixelShader> myPixelShader;
	
	ComPtr<ID3D11InputLayout> myInputLayout;
};
