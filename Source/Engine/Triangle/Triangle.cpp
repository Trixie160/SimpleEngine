#include <d3d11.h>
#include <fstream>
#include "Triangle.h"

struct Vertex
{
	float x, y, z, w;
	float r, g, b, a;
};

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

bool Triangle::Init(ID3D11Device* aDevice)
{
	HRESULT result = {};

	Vertex vertices[3] =
	{
		{-1.0f, 0.0f,0,1,1,0,0,1},
		{1.0f,0.0f,0,1,0,1,0,1},
		{0.0f,1.0f,0,1,0,0,1,1}
	};

	unsigned int indices[3] =
	{
		0,1,2
	};

	{ //Create Vertex Buffer
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = { 0 };
		vertexData.pSysMem = vertices;

		vertexBufferDesc.ByteWidth = sizeof(vertices);
		result = aDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &myVertexBuffer);
		if (FAILED(result))
			return false;
	}

	{ //Create Index Buffer
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = { 0 };
		indexData.pSysMem = indices;

		indexBufferDesc.ByteWidth = sizeof(indices);
		result = aDevice->CreateBuffer(&indexBufferDesc, &indexData, &myIndexBuffer);
		if (FAILED(result))
			return false;
	}


	//Load shaders
	std::string vsData;
	std::string psData;
	std::ifstream vsFile;
	std::ifstream psFile;

	{ 
		vsFile.open("../../Lib/TriangleVS.cso", std::ios::binary);
		vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
		result = aDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &myVertexShader);

		if (FAILED(result))
			return false;

		vsFile.close();
	}

	{
		psFile.open("../../Lib/TrianglePS.cso", std::ios::binary);
		psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
		result = aDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &myPixelShader);

		if (FAILED(result))
			return false;

		psFile.close();
	}

	{ //Create Inputlayout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0},
		};

		result = aDevice->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &myInputLayout);

		if (FAILED(result))
			return false;
	}

	return true;
}

void Triangle::Render(ID3D11DeviceContext* aContext)
{
	aContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	aContext->IASetInputLayout(myInputLayout.Get());

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	aContext->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &stride, &offset);
	aContext->IASetIndexBuffer(myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	aContext->VSSetShader(myVertexShader.Get(), nullptr, 0);
	aContext->PSSetShader(myPixelShader.Get(), nullptr, 0);
	aContext->DrawIndexed(3, 0, 0);
}

