#pragma once
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Device;
struct ID3D11DeviceContext;

class Shader
{
public:
	Shader();
	~Shader();

	bool Init(ID3D11Device* aDevice, std::vector<D3D11_INPUT_ELEMENT_DESC> aInputLayout,const std::string& aPSFileName, const std::string& aVSFileName);
	void SetShader(ID3D11DeviceContext* aContext);
private:
	ComPtr<ID3D11VertexShader> myVertexShader;
	ComPtr<ID3D11PixelShader> myPixelShader;
	ComPtr<ID3D11InputLayout> myInputLayout;
};
