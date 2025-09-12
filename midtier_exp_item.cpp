//********************************************************************************
//
// midtier_exp_item.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#include <random>

#include "midtier_exp_item.h"

MidTierExpItem::MidTierExpItem()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\MidTierEXPItem.obj");

	m_Scale = { 1.0f , 1.0f , 1.0f };


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\pixelLightingBlinnPhongVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\pixelLightingBlinnPhongPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	std::random_device rd;
	m_Exp = rd() % 30 + 21;
}

MidTierExpItem::~MidTierExpItem()
{
	delete m_pModelRenderer;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release(); 
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}
