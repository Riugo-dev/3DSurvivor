//********************************************************************************
//
// model_manager.h[モデルの管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/19
//********************************************************************************
#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

#include "shader_manager.h"
#include	<unordered_map>
#include	<memory>

typedef enum
{
	MODEL_NONE = -1,

	//経験値アイテム
	LOWTIER_EXP,
	MIDTIER_EXP,
	HIGHTIER_EXP,

	//その他ドロップアイテム
	ITEM_HEAL,
	ITEM_VACUUM,
	ITEM_BOOST,
	ITEM_DOUBLEPOINTS,

	//プレイヤーモデル
	PLAYER,

	//敵モデル
	ENEMY_RED,
	ENEMY_BLUE,
	ENEMY_GREEN,
	ENEMY_PURPLE,
	ENEMY_SILVER,
	ENEMY_BLACK,

	//射撃敵モデル
	SHOOTER_ENEMY_RED,
	SHOOTER_ENEMY_BLUE,
	SHOOTER_ENEMY_GREEN,
	SHOOTER_ENEMY_PURPLE,
	SHOOTER_ENEMY_SILVER,

	//スワーム敵モデル
	SWARM_ENEMY_RED,
	SWARM_ENEMY_SILVER,

	//中ボス敵モデル
	MIDBOSS_RED,

	//敵の玉
	ENEMYBULLET,

	//武器モデル
	BULLET,
	SHURIKEN,
	SWORD,
	BOMB,

	//その他のオブジェクト
	SKYDOME,
	SHADOW,
	
}ModelTags;

class ModelManager
{
private:

	static std::unordered_map<ModelTags , std::unique_ptr<class ModelRenderer>> m_pModelRenderers;
	static std::unordered_map< ModelTags, std::unique_ptr<class ShaderManager>> m_pModelShaders;
public:
	ModelManager();
	~ModelManager();

	static void Init();
	static void InitTitle();

	static void ModelDraw(ModelTags);
	static void ModelDrawAlpha(ModelTags, float aplha = 1.0f);
	static void SetShaders(ModelTags, Shader);
	static ModelRenderer* GetModelRenderers(ModelTags);
	static ShaderManager* GetShaderManager(ModelTags);
};

#endif // !_MODEL_MANAGER_H_
