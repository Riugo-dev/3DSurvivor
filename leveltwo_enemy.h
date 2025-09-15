//********************************************************************************
//
// leveltwo_enemy.h[ƒŒƒxƒ‹2“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _LEVELTWO_ENEMY_H_
#define _LEVELTWO_ENEMY_H_

#include "enemybase.h"

class LevelTwoEnemy : public BaseEnemy
{
public:
	LevelTwoEnemy();
	~LevelTwoEnemy();

	void EnemyItemDrop() override;
};

#endif // !_LEVELTWO_ENEMY_H_

