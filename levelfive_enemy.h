//********************************************************************************
//
// levelfive_enemy.h[ƒŒƒxƒ‹5“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************

#ifndef _LEVELFIVE_ENEMY_H_
#define _LEVELFIVE_ENEMY_H_

#include "enemybase.h"

class LevelFiveEnemy : public BaseEnemy
{
public:
	LevelFiveEnemy();
	~LevelFiveEnemy();

	void EnemyItemDrop() override;
};

#endif // !_LEVELFIVE_ENEMY_H_


