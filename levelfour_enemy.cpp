//********************************************************************************
//
// levelfour_enemy.cpp[ƒŒƒxƒ‹4“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include <random>
#include "midtier_exp_item.h"
#include "hightier_exp_item.h"

#include "levelfour_enemy.h"

LevelFourEnemy::LevelFourEnemy()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\EnemyTypePurple.obj");

	m_Scale = { 0.5f , 0.5f , 0.5f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\toon1VS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\toon1PS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	m_HP = 8;
	m_EnemySpeed = 0.04f;
	m_Points = 40;
}

LevelFourEnemy::~LevelFourEnemy()
{
	delete m_pModelRenderer;
	m_pModelRenderer = nullptr;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}

void LevelFourEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 0.5f, 0.0f));
	}
	else
	{
		Manager::GetScene()->AddGameObject<MidTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 0.5f, 0.0f));
	}
}

