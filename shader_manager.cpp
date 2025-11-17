//********************************************************************************
//
// shader_manager.h[音声エフェクトマネージャー]
//
//															Author :Riugo Honda
//															Date   :2025/09/22
//********************************************************************************
#include "main.h"
#include "renderer.h"

#include "shader_manager.h"
//********************************************************************************
//グローバル変数
//********************************************************************************

//std::unordered_map<Shader, ShaderPointers*> ShaderManager::m_pShaderPointers;

//********************************************************************************
//シェーダ―関数
//********************************************************************************
ShaderPointers::ShaderPointers()
{
	m_pVertexLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
}
 
ShaderPointers::~ShaderPointers()
{
	m_pVertexLayout->Release();
	m_pVertexShader->Release();
	m_pPixelShader->Release();
}

void ShaderPointers::SetShaderPointers(ID3D11VertexShader* vs, ID3D11PixelShader* ps, ID3D11InputLayout* vl)
{
	m_pVertexShader = vs;
	m_pPixelShader = ps;
	m_pVertexLayout = vl;
}


//********************************************************************************
//シェーダ―マネージャー関数
//********************************************************************************
ShaderManager::ShaderManager(Shader shader , bool flag)
{
	switch (shader)
	{
	case SHADER_UNLITTEXT:
	{
		m_pShaderPointers[SHADER_UNLITTEXT] = new ShaderPointers;
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* vl;
		Renderer::CreateVertexShader(&vs, &vl, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&ps, "shader\\unlitTexturePS.cso");
		m_pShaderPointers[SHADER_UNLITTEXT]->SetShaderPointers(vs, ps, vl);
	}
		break;
	case SHADER_TOON:
	{
		m_pShaderPointers[SHADER_TOON] = new ShaderPointers;
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* vl;
		Renderer::CreateVertexShader(&vs, &vl, "shader\\toon1VS.cso");
		Renderer::CreatePixelShader(&ps, "shader\\toon1PS.cso");
		m_pShaderPointers[SHADER_TOON]->SetShaderPointers(vs, ps, vl);
	}
		break;
	case SHADER_BLINNPHONG:
	{
		m_pShaderPointers[SHADER_BLINNPHONG] = new ShaderPointers;
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* vl;
		Renderer::CreateVertexShader(&vs, &vl, "shader\\pixelLightingBlinnPhongVS.cso");
		Renderer::CreatePixelShader(&ps, "shader\\pixelLightingBlinnPhongPS.cso");
		m_pShaderPointers[SHADER_BLINNPHONG]->SetShaderPointers(vs, ps, vl);
	}
		break;
	case SHADER_TOON_TWO:
	{
		m_pShaderPointers[SHADER_TOON_TWO] = new ShaderPointers;
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* vl;
		Renderer::CreateVertexShader(&vs, &vl, "shader\\toon2VS.cso");
		Renderer::CreatePixelShader(&ps, "shader\\toon2PS.cso");
		m_pShaderPointers[SHADER_TOON_TWO]->SetShaderPointers(vs, ps, vl);
	}
		break;
	case SHADER_DIRECTIONLIGHTING:
	{
		m_pShaderPointers[SHADER_DIRECTIONLIGHTING] = new ShaderPointers;
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* vl;
		Renderer::CreateVertexShader(&vs, &vl, "shader\\vertexDirectionalLightingVS.cso");
		Renderer::CreatePixelShader(&ps, "shader\\vertexDirectionalLightingPS.cso");
		m_pShaderPointers[SHADER_DIRECTIONLIGHTING]->SetShaderPointers(vs, ps, vl);
	}
	case SHADER_INSTANCETOON:
	{
		m_pShaderPointers[SHADER_INSTANCETOON] = new ShaderPointers;
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* vl;
		Renderer::CreateVertexShader(&vs, &vl, "shader\\instancetoonVS.cso");
		Renderer::CreatePixelShader(&ps, "shader\\toon1PS.cso");
		m_pShaderPointers[SHADER_INSTANCETOON]->SetShaderPointers(vs, ps, vl);

	}
		break;
	}

	

	

	if(flag)
	{
		m_pShaderPointers[SHADER_TOONEDGE] = new ShaderPointers;
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* vl;
		Renderer::CreateVertexShader(&vs, &vl, "shader\\ToonVSEdge.cso");
		Renderer::CreatePixelShader(&ps, "shader\\ToonPSEdge.cso");
		m_pShaderPointers[SHADER_TOONEDGE]->SetShaderPointers(vs, ps, vl);
	}

	

	


}

ShaderManager::~ShaderManager()
{
	for (auto itr : m_pShaderPointers)
	{
		delete itr.second;
	}

	m_pShaderPointers.clear();
}

ShaderPointers* ShaderManager::GetShaderPointers(Shader shader)
{
	if (m_pShaderPointers.count(shader))
	{
		return m_pShaderPointers[shader];
	}

	return nullptr;
}

void ShaderManager::SetShaders(Shader shader)
{
	Renderer::GetDeviceContext()->IASetInputLayout(m_pShaderPointers[shader]->GetVertexLayout());

	Renderer::GetDeviceContext()->VSSetShader(m_pShaderPointers[shader]->GetVertexShader(), NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_pShaderPointers[shader]->GetPixelShader(), NULL, 0);
}



