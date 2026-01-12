//********************************************************************************
//
// levelone_swarmenemy.h[レベル１ダッシュ敵クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/09
//********************************************************************************

#ifndef _LEVELONE_SWARMENEMY_H_
#define _LEVELONE_SWARMENEMY_H_

#include "swarmenemybase.h"

class LevelOneSwarmEnemy : public SwarmBaseEnemy
{
public:
	LevelOneSwarmEnemy() = default;
	~LevelOneSwarmEnemy() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void EnemyItemDrop() override;
};

#endif // !_LEVELONE_SWARMENEMY_H_
