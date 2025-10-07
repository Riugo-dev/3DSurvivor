//********************************************************************************
//
// enemy_bullet.h[“G‚Ì’e‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/06
//********************************************************************************
#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

#include "gameobject.h"
#include "model_manager.h"
#include "manager_shader.h"

class EnemyBullet : public GameObject
{
private:
	ModelTags m_ModelTag;
	Shader m_Shader;
	Vector3 m_Velocity;
	int m_LivingFrame;
	int m_LifeTime;
	int m_Hp;
public:
	EnemyBullet();
	~EnemyBullet();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetBullet(Vector3);
};

#endif // !_ENEMY_BULLET_H_

