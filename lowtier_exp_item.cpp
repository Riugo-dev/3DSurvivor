//********************************************************************************
//
// lowtier_exp_item.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#include <random>

#include "lowtier_exp_item.h"

LowTierExpItem::LowTierExpItem()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\LowTierEXPItem.obj");

	m_Scale = { 1.0f , 1.0f , 1.0f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	std::random_device rd;
	m_Exp = rd() % 15 + 5;

}

LowTierExpItem::~LowTierExpItem()
{
	delete m_pModelRenderer;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}
