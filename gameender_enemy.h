//********************************************************************************
//
// gameender_enemy.h[éÄê_ìGÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************

#ifndef _GAMEENDER_ENEMY_H_
#define _GAMEENDER_ENEMY_H_

#include "enemybase.h"

class GameEnderEnemy : public BaseEnemy
{
public:
	GameEnderEnemy();
	~GameEnderEnemy();

	void EnemyItemDrop() override;
};

#endif // !_GAMEENDER_ENEMY_H_


