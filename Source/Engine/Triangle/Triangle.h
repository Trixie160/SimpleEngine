#pragma once
#include <wrl/client.h>
#include <string>
#include <vector>

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

struct Vertex2
{
	float x, y, z, w;
	float r, g, b, a;
};

struct TriangleData
{
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;

	ComPtr<ID3D11InputLayout> inputLayout;

	int indicesSize;
};

class Triangle
{
public:
	Triangle();
	~Triangle();

	bool Init(ID3D11Device* aDevice);
	void Render(ID3D11DeviceContext* aContext);
private:
	bool InitBuffers(ID3D11Device* aDevice, TriangleData& aTriangleData, const std::string& aPSFileName, const std::string& aVSFileName);
private:
	ComPtr<ID3D11Buffer> myTimeBuffer;

	TriangleData myTriangle;
};
