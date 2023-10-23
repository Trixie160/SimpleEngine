#pragma once
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

struct ID3D11Device;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11Buffer;

struct Vertex
{
	SimpleUtilities::Vector4f position;
	SimpleUtilities::Vector4f color;
};

class Model
{
public:
	Model();
	~Model();

	void Init(const std::vector<Vertex>& aVertices, const std::vector<unsigned int>& aIndices, const SimpleUtilities::Matrix4x4f& aModelToWorld, ID3D11Device* aDevice);
public:
	SimpleUtilities::Matrix4x4f GetModelToWorldMatrix();
	std::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	ComPtr<ID3D11Buffer> GetVertexBuffer();
	ComPtr<ID3D11Buffer> GetIndexBuffer();
	int GetIndexCount();
private:
	std::vector<Vertex> myVertices;
	std::vector<unsigned int> myIndices;

	SimpleUtilities::Matrix4x4f myModelToWorld;

	ComPtr<ID3D11Buffer> myVertexBuffer;
	ComPtr<ID3D11Buffer> myIndexBuffer;
};
