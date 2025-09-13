//********************************************************************************
//
// levelthree_enemy.cpp[ƒŒƒxƒ‹3“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include <random>
#include "lowtier_exp_item.h"
#include "midtier_exp_item.h"

#include "levelthree_enemy.h"

LevelThreeEnemy::LevelThreeEnemy()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\EnemyTypeGreen.obj");

	m_Scale = { 0.5f , 0.5f , 0.5f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\toon1VS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\toon1PS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	m_HP = 3;
	m_EnemySpeed = 0.02f;
	m_Points = 30;
}

LevelThreeEnemy::~LevelThreeEnemy()
{
	delete m_pModelRenderer;
	m_pModelRenderer = nullptr;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}

void LevelThreeEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 0.5f, 0.0f));
	}
	else
	{
		Manager::GetScene()->AddGameObject<MidTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 0.5f, 0.0f));
	}
}
