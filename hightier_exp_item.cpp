//********************************************************************************
//
// hightier_exp_item.cpp[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#include	<random>

#include "hightier_exp_item.h"

HighTierExpItem::HighTierExpItem(Vector3 position)
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\HighTierItem.obj");

	m_Scale = { 1.0f , 1.0f , 1.0f };

	m_Position = position;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	std::random_device rd;
	m_Exp = rd() % 50 + 51;
}

HighTierExpItem::~HighTierExpItem()
{
	delete m_pModelRenderer;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}
