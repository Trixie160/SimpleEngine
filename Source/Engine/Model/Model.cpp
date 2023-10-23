#include "stdafx.h"
#include <cassert>
#include <d3d11.h>
#include "Model/Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Init(const std::vector<Vertex>& aVertices, const std::vector<unsigned int>& aIndices, const SimpleUtilities::Matrix4x4f& aModelToWorld, ID3D11Device* aDevice)
{
	myVertices = aVertices;
	myIndices = aIndices;
	myModelToWorld = aModelToWorld;

	{
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(Vertex) * static_cast<int>(myVertices.size());
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = &myVertices[0];
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		HRESULT result = aDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &myVertexBuffer);
		if (FAILED(result))
			assert(false && "Could not create vertex buffer");
	}

	{
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned int) * static_cast<int>(myIndices.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = &myIndices[0];
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;
		HRESULT result = aDevice->CreateBuffer(&indexBufferDesc, &indexData, &myIndexBuffer);
		if (FAILED(result))
			assert(false && "Could not create index buffer");
	}

}

int Model::GetIndexCount()
{
	return static_cast<int>(myIndices.size());
}

ComPtr<ID3D11Buffer> Model::GetVertexBuffer()
{
	return myVertexBuffer;
}

ComPtr<ID3D11Buffer> Model::GetIndexBuffer()
{
	return myIndexBuffer;
}

SimpleUtilities::Matrix4x4f Model::GetModelToWorldMatrix()
{
	return myModelToWorld;
}

std::vector<D3D11_INPUT_ELEMENT_DESC> Model::GetInputLayout()
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	return inputLayout;
}
