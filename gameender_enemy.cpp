//********************************************************************************
//
// gameender_enemy.h[Ž€_“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#include "hightier_exp_item.h"

#include "gameender_enemy.h"

GameEnderEnemy::GameEnderEnemy()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\EnemyTypeBlack.obj");

	m_Scale = { 0.5f , 0.5f , 0.5f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\pixelLightingBlinnPhongVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\pixelLightingBlinnPhongPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	m_HP = 100;
	m_EnemySpeed = 0.4f;
	m_Points = 10000;
}

GameEnderEnemy::~GameEnderEnemy()
{
	delete m_pModelRenderer;
	m_pModelRenderer = nullptr;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}

void GameEnderEnemy::EnemyItemDrop()
{
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.25f, 1.0f, 0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.25f, 1.0f, -0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.25f, 1.0f, -0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.25f, 1.0f, 0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.0f, 1.0f, 0.0f));

}

