//********************************************************************************
//
// model_manager.cpp[モデルの管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/19
//********************************************************************************
#include "main.h"
#include "renderer.h"



#include "model_manager.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
std::unordered_map<ModelTags, std::unique_ptr<ModelRenderer>> ModelManager::m_pModelRenderers;
std::unordered_map< ModelTags, std::unique_ptr<ShaderManager>> ModelManager::m_pModelShaders;
//********************************************************************************
//関数
//********************************************************************************
ModelManager::ModelManager()
{
	m_pModelRenderers[LOWTIER_EXP] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[LOWTIER_EXP]->Load("asset\\model\\LowTierEXPItem.obj");
	m_pModelShaders[LOWTIER_EXP] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG , true);

	m_pModelRenderers[MIDTIER_EXP] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[MIDTIER_EXP]->Load("asset\\model\\MidTierEXPItem.obj");
	m_pModelShaders[MIDTIER_EXP] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG, true);

	m_pModelRenderers[HIGHTIER_EXP] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[HIGHTIER_EXP]->Load("asset\\model\\HighTierEXPItem.obj");
	m_pModelShaders[HIGHTIER_EXP] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG, true);

	m_pModelRenderers[ITEM_HEAL] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ITEM_HEAL]->Load("asset\\model\\ItemTypeHeal.obj");
	m_pModelShaders[ITEM_HEAL] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[ITEM_VACUUM] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ITEM_VACUUM]->Load("asset\\model\\ItemTypeGather.obj");
	m_pModelShaders[ITEM_VACUUM] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG, true);

	m_pModelRenderers[ITEM_BOOST] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ITEM_BOOST]->Load("asset\\model\\ItemTypeBoost.obj");
	m_pModelShaders[ITEM_BOOST] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[PLAYER] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[PLAYER]->Load("asset\\model\\player.obj");
	m_pModelShaders[PLAYER] = std::make_unique<ShaderManager>(SHADER_TOON);

	m_pModelRenderers[ENEMY_RED] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_RED]->Load("asset\\model\\EnemyTypeRed.obj");
	m_pModelShaders[ENEMY_RED] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[ENEMY_BLUE] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_BLUE]->Load("asset\\model\\EnemyTypeBlue.obj");
	m_pModelShaders[ENEMY_BLUE] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[ENEMY_GREEN] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_GREEN]->Load("asset\\model\\EnemyTypeGreen.obj");
	m_pModelShaders[ENEMY_GREEN] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[ENEMY_PURPLE] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_PURPLE]->Load("asset\\model\\EnemyTypePurple.obj");
	m_pModelShaders[ENEMY_PURPLE] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[ENEMY_SILVER] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_SILVER]->Load("asset\\model\\EnemyTypeMetal.obj");
	m_pModelShaders[ENEMY_SILVER] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG, true);

	m_pModelRenderers[ENEMY_BLACK] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[ENEMY_BLACK]->Load("asset\\model\\EnemyTypeBlack.obj");
	m_pModelShaders[ENEMY_BLACK] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG, true);

	m_pModelRenderers[SHOOTER_ENEMY_RED] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SHOOTER_ENEMY_RED]->Load("asset\\model\\EnemyShooterRed.obj");
	m_pModelShaders[SHOOTER_ENEMY_RED] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[SHOOTER_ENEMY_BLUE] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SHOOTER_ENEMY_BLUE]->Load("asset\\model\\EnemyShooterBlue.obj");
	m_pModelShaders[SHOOTER_ENEMY_BLUE] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[SHOOTER_ENEMY_GREEN] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SHOOTER_ENEMY_GREEN]->Load("asset\\model\\EnemyShooterGreen.obj");
	m_pModelShaders[SHOOTER_ENEMY_GREEN] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[SHOOTER_ENEMY_PURPLE] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SHOOTER_ENEMY_PURPLE]->Load("asset\\model\\EnemyShooterPurple.obj");
	m_pModelShaders[SHOOTER_ENEMY_PURPLE] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[SHOOTER_ENEMY_SILVER] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SHOOTER_ENEMY_SILVER]->Load("asset\\model\\EnemyShooterMetal.obj");
	m_pModelShaders[SHOOTER_ENEMY_SILVER] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG, true);
	
	m_pModelRenderers[SWARM_ENEMY_RED] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SWARM_ENEMY_RED]->Load("asset\\model\\EnemySwarmRed.obj");
	m_pModelShaders[SWARM_ENEMY_RED] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[SWARM_ENEMY_SILVER] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SWARM_ENEMY_SILVER]->Load("asset\\model\\EnemySwarmMetal.obj");
	m_pModelShaders[SWARM_ENEMY_SILVER] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG, true);

	m_pModelRenderers[MIDBOSS_RED] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[MIDBOSS_RED]->Load("asset\\model\\EnemyBossRed.obj");
	m_pModelShaders[MIDBOSS_RED] = std::make_unique<ShaderManager>(SHADER_TOON, true);

	m_pModelRenderers[BULLET] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[BULLET]->Load("asset\\model\\bullet.obj");
	m_pModelShaders[BULLET] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG);

	m_pModelRenderers[SHURIKEN] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SHURIKEN]->Load("asset\\model\\AttackTypeShuriken.obj");
	m_pModelShaders[SHURIKEN] = std::make_unique<ShaderManager>(SHADER_TOON);

	m_pModelRenderers[SWORD] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SWORD]->Load("asset\\model\\AttackTypeSword.obj");
	m_pModelShaders[SWORD] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG);

	m_pModelRenderers[BOMB] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[BOMB]->Load("asset\\model\\AttackTypeBomb.obj");
	m_pModelShaders[BOMB] = std::make_unique<ShaderManager>(SHADER_BLINNPHONG);


	m_pModelRenderers[SKYDOME] = std::make_unique<ModelRenderer>();
	m_pModelRenderers[SKYDOME]->Load("asset\\model\\sky.obj");
	m_pModelShaders[SKYDOME] = std::make_unique<ShaderManager>(SHADER_UNLITTEXT);



}

ModelManager::~ModelManager()
{
	m_pModelRenderers.clear();
	m_pModelShaders.clear();

	//ModelRenderer::UnloadAll();
}

void ModelManager::ModelDraw(ModelTags modeltag)
{
	if (m_pModelRenderers.count(modeltag))
	{
		m_pModelRenderers[modeltag]->Draw();
	}
}

void ModelManager::SetShaders(ModelTags model, Shader shader)
{
	if (m_pModelShaders.count(model))
	{
		m_pModelShaders[model]->SetShaders(shader);
	}
}

//ShaderManager* ModelManager::GetShaders(ModelTags model)
//{
//	return m_pModelShaders[model];
//}
//
//ModelRenderer* ModelManager::GetModel(ModelTags model)
//{
//	return m_pModelRenderers[model];
//}
