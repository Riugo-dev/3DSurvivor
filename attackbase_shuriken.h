//********************************************************************************
//
// attackbase_shuriken.h[‹…UŒ‚‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#ifndef  _ATTACKBASE_SHURIKEN_H_
#define  _ATTACKBASE_SHURIKEN_H_

#include "attackbase.h"

class BaseAttackShuriken : public BaseAttack
{
private:
	float m_rotationspeed;
	float m_radius;
	float m_angle;
	XMVECTOR m_direction;
public:
	BaseAttackShuriken();
	~BaseAttackShuriken();

	void Update() override;

	void SetShuriken(float rad, float speed, Vector3 pos, float angle);
};

#endif // ! _ATTACKBASE_SHURIKEN_H_
