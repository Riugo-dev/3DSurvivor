//********************************************************************************
//
// levelthree_enemy.h[ƒŒƒxƒ‹3“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _LEVELTHREE_ENEMY_H_
#define _LEVELTHREE_ENEMY_H_

#include "enemybase.h"

class LevelThreeEnemy : public BaseEnemy
{
public:
	LevelThreeEnemy() = default;
	~LevelThreeEnemy() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELTHREE_ENEMY_H_

