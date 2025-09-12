//********************************************************************************
//
// levelone_enemy.h[ƒŒƒxƒ‹‚P“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include <random>
#include "lowtier_exp_item.h"

#include "levelone_enemy.h"

LevelOneEnemy::LevelOneEnemy()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\EnemyTypeRed.obj");

	m_Scale = { 0.5f , 0.5f , 0.5f };

	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");*/

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\toon1VS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\toon1PS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\pixelLightingBlinnPhongVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\pixelLightingBlinnPhongPS.cso");*/

	m_HP = 1;
	m_EnemySpeed = 0.01f;
	m_Points = 10;
}

LevelOneEnemy::~LevelOneEnemy()
{
	delete m_pModelRenderer;
	m_pModelRenderer = nullptr;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}

void LevelOneEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 80)
	{
		Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 1.0f, 0.0f));
	}
}
