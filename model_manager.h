//********************************************************************************
//
// model_manager.h[モデルの管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/19
//********************************************************************************
#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

#include	<unordered_map>
#include	<memory>

typedef enum
{
	MODEL_NONE = -1,

	//経験値アイテム
	LOWTIER_EXP,
	MIDTIER_EXP,
	HIGHTIER_EXP,

	//プレイヤーモデル
	PLAYER,

	//敵モデル
	ENEMY_RED,
	ENEMY_BLUE,
	ENEMY_GREEN,
	ENEMY_PURPLE,
	ENEMY_SILVER,
	ENEMY_BLACK,

	//武器モデル
	BULLET,
	SHURIKEN,
	SWORD,

	
}ModelTags;

class ModelManager
{
private:

	static std::unordered_map<ModelTags , std::unique_ptr<class ModelRenderer>> m_pModelRenderers;
public:
	ModelManager();
	~ModelManager();


	static void ModelDraw(ModelTags);
};

#endif // !_MODEL_MANAGER_H_
