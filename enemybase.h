//********************************************************************************
//
// enemybase.h[“G‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/08
//********************************************************************************
#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_

#include "main.h"
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "attackbase.h"
#include "model_manager.h"
#include "shader_manager.h"


#define ENEMY_LIVINGFRAME (5400) //–ñ‚X‚O•b

class BaseEnemy : public GameObject
{
protected:


	//ModelRenderer* m_pModelRenderer = nullptr;

	int m_HP;
	float m_EnemySpeed = 0.03f;
	int m_Points;
	ModelTags m_ModelTag;
	Shader m_Shader;
	int m_FrameCount = 0;
	bool m_GetBig = false;
	const float m_Radius = 1.0f;
	Player* m_pPlayer = nullptr;
	std::vector<BaseAttack*> m_Attacks;
public:
	~BaseEnemy() = default;

	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {}
	virtual void Draw()	override{}

	ModelTags GetModelTag() { return m_ModelTag; }
	Shader GetShader() { return m_Shader; }

	void DamageEnemy(int damage)
	{
		m_HP -= damage;
	}
	int GetEnemyHp() { return m_HP; }

	virtual void EnemyItemDrop() = 0;
	
	void UpdateAttacks(std::vector<BaseAttack*> att)
	{
		m_Attacks.clear();

		m_Attacks = att;
	}

};

#endif // !_ENEMYBASE_H_

