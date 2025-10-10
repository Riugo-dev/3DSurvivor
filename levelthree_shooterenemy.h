//********************************************************************************
//
// levelthree_shooterenemy.h[ƒŒƒxƒ‹3ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************

#ifndef _LEVELTHREE_SHOOTERENEMY_H_
#define _LEVELTHREE_SHOOTERENEMY_H_

#include "shooterenemybase.h"

class LevelThreeShooterEnemy : public ShooterBaseEnemy
{
public:
	LevelThreeShooterEnemy();
	~LevelThreeShooterEnemy()override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELTHREE_SHOOTERENEMY_H_
