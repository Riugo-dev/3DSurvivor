//********************************************************************************
//
// levelone_enemy.h[ƒŒƒxƒ‹‚P“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _LEVELONE_ENEMY_H_
#define _LEVELONE_ENEMY_H_

#include "enemybase.h"

class LevelOneEnemy : public BaseEnemy
{
public:
	LevelOneEnemy();
	~LevelOneEnemy();

	void EnemyItemDrop() override;
};

#endif // !_LEVELONE_ENEMY_H_
