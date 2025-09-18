//********************************************************************************
//
// levelfive_enemy.h[ƒŒƒxƒ‹5“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************

#include <random>
#include "hightier_exp_item.h"

#include "levelfive_enemy.h"

LevelFiveEnemy::LevelFiveEnemy()
{
	//m_pModelRenderer = new ModelRenderer();
	//m_pModelRenderer->Load("asset\\model\\EnemyTypeMetal.obj");

	m_Scale = { 0.5f , 0.5f , 0.5f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\pixelLightingBlinnPhongVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\pixelLightingBlinnPhongPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	m_HP = 10;
	m_EnemySpeed = 0.05f;
	m_Points = 100;
	m_ModelTag = ENEMY_SILVER;
}

LevelFiveEnemy::~LevelFiveEnemy()
{
	//delete m_pModelRenderer;
	//m_pModelRenderer = nullptr;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}

void LevelFiveEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.25f, 0.5f, 0.0f));
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.25f, 0.5f, 0.0f));
	}
	else
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 0.5f, 0.0f));
	}
}

