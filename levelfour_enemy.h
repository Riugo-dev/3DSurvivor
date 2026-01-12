//********************************************************************************
//
// levelfour_enemy.h[ƒŒƒxƒ‹4“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _LEVELFOUR_ENEMY_H_
#define _LEVELFOUR_ENEMY_H_

#include "enemybase.h"

class LevelFourEnemy : public BaseEnemy
{
public:
	LevelFourEnemy() = default;
	~LevelFourEnemy() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELFOUR_ENEMY_H_

