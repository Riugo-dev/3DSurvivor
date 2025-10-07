//********************************************************************************
//
// levelfour_shooterenemy.h[ƒŒƒxƒ‹4ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************

#ifndef _LEVELFOUR_SHOOTERENEMY_H_
#define _LEVELFOUR_SHOOTERENEMY_H_

#include "shooterenemybase.h"

class LevelFourShooterEnemy : public ShooterBaseEnemy
{
public:
	LevelFourShooterEnemy();
	~LevelFourShooterEnemy()override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELFOUR_SHOOTERENEMY_H_
