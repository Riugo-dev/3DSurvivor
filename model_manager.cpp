//********************************************************************************
//
// model_manager.cpp[モデルの管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/19
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include"modelRenderer.h"

#include "model_manager.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
std::unordered_map<ModelTags, std::unique_ptr<ModelRenderer>> ModelManager::m_pModelRenderers;
//********************************************************************************
//関数
//********************************************************************************
ModelManager::ModelManager()
{
	m_pModelRenderers[LOWTIER_EXP] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[LOWTIER_EXP]->Load("asset\\model\\LowTierEXPItem.obj");
	m_pModelRenderers[MIDTIER_EXP] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[MIDTIER_EXP]->Load("asset\\model\\MidTierEXPItem.obj");
	m_pModelRenderers[HIGHTIER_EXP] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[HIGHTIER_EXP]->Load("asset\\model\\HighTierEXPItem.obj");

	m_pModelRenderers[PLAYER] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[PLAYER]->Load("asset\\model\\player.obj");

	m_pModelRenderers[ENEMY_RED] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_RED]->Load("asset\\model\\EnemyTypeRed.obj");
	m_pModelRenderers[ENEMY_BLUE] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_BLUE]->Load("asset\\model\\EnemyTypeBlue.obj");
	m_pModelRenderers[ENEMY_GREEN] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_GREEN]->Load("asset\\model\\EnemyTypeGreen.obj");
	m_pModelRenderers[ENEMY_PURPLE] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_PURPLE]->Load("asset\\model\\EnemyTypePurple.obj");
	m_pModelRenderers[ENEMY_SILVER] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_SILVER]->Load("asset\\model\\EnemyTypeMetal.obj");
	m_pModelRenderers[ENEMY_BLACK] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_BLACK]->Load("asset\\model\\EnemyTypeBlack.obj");

	m_pModelRenderers[BULLET] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[BULLET]->Load("asset\\model\\bullet.obj");
	m_pModelRenderers[SHURIKEN] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SHURIKEN]->Load("asset\\model\\AttackTypeShuriken.obj");
	m_pModelRenderers[SWORD] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SWORD]->Load("asset\\model\\AttackTypeSword.obj");

	m_pModelRenderers[SKYDOME] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SKYDOME]->Load("asset\\model\\sky.obj");



}

ModelManager::~ModelManager()
{
	m_pModelRenderers.clear();


	ModelRenderer::UnloadAll();
}

void ModelManager::ModelDraw(ModelTags modeltag)
{
	if (m_pModelRenderers.count(modeltag))
	{
		m_pModelRenderers[modeltag]->Draw();
	}
}
