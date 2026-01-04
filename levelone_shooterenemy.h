//********************************************************************************
//
// levelone_shooterenemy.h[ƒŒƒxƒ‹‚PŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/06
//********************************************************************************

#ifndef _LEVELONE_SHOOTERENEMY_H_
#define _LEVELONE_SHOOTERENEMY_H_

#include "shooterenemybase.h"

class LevelOneShooterEnemy : public ShooterBaseEnemy
{
public :
	LevelOneShooterEnemy() = default;
	~LevelOneShooterEnemy()override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELONE_SHOOTERENEMY_H_
