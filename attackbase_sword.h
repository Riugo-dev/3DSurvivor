//********************************************************************************
//
// attackbase_sword.h[ãÖçUåÇÇÃäÓíÍÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#ifndef  _ATTACKBASE_SWORD_H_
#define  _ATTACKBASE_SWORD_H_

#include "attackbase.h"

class BaseAttackSword : public BaseAttack
{
private:
	float m_rotationspeed;
	float m_radius;
	float m_angle;
	const float m_gravity = -0.5f;
public:
	BaseAttackSword();
	~BaseAttackSword();

	void Update() override;

	void SetSword(Vector3 vel, Vector3 pos, float angle);
};

#endif // ! _ATTACKBASE_SWORD_H_
