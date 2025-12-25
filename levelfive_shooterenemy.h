//********************************************************************************
//
// levelfive_shooterenemy.h[ƒŒƒxƒ‹5ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************

#ifndef _LEVELFIVE_SHOOTERENEMY_H_
#define _LEVELFIVE_SHOOTERENEMY_H_

#include "shooterenemybase.h"

class LevelFiveShooterEnemy : public ShooterBaseEnemy
{
public:
	LevelFiveShooterEnemy() = default;
	~LevelFiveShooterEnemy()override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELFIVE_SHOOTERENEMY_H_

