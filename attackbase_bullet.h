//********************************************************************************
//
// attackbase_bullet.h[‹…UŒ‚‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#ifndef  _ATTACKBASE_BULLET_H_
#define  _ATTACKBASE_BULLET_H_

#include "attackbase.h"

class BaseAttackBullet : public BaseAttack
{
public:
	BaseAttackBullet();
	~BaseAttackBullet();

	void Update() override;
};

#endif // ! _ATTACKBASE_BULLET_H_
