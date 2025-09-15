//********************************************************************************
//
// hightier_exp_item.cpp[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#include	<random>

#include "hightier_exp_item.h"

HighTierExpItem::HighTierExpItem()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\HighTierEXPItem.obj");

	m_Scale = { 1.0f , 1.0f , 1.0f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\pixelLightingBlinnPhongVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\pixelLightingBlinnPhongPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	std::random_device rd;
	m_Exp = rd() % 100 + 51;
}

HighTierExpItem::~HighTierExpItem()
{
	delete m_pModelRenderer;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}
