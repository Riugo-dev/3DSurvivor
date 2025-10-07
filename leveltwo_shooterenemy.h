//********************************************************************************
//
// leveltwo_shooterenemy.h[ƒŒƒxƒ‹2ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************

#ifndef _LEVELTWO_SHOOTERENEMY_H_
#define _LEVELTWO_SHOOTERENEMY_H_

#include "shooterenemybase.h"

class LevelTwoShooterEnemy : public ShooterBaseEnemy
{
public:
	LevelTwoShooterEnemy();
	~LevelTwoShooterEnemy()override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELTWO_SHOOTERENEMY_H_
