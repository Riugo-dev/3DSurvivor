//********************************************************************************
//
// itemdrop_swarmenemy.h[アイテムドロップダッシュ敵クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/30
//********************************************************************************

#ifndef _ITEMDROP_SWARMENEMY_H_
#define _ITEMDROP_SWARMENEMY_H_

#include "swarmenemybase.h"

class ItemDropSwarmEnemy : public SwarmBaseEnemy
{
public:
	ItemDropSwarmEnemy();
	~ItemDropSwarmEnemy() override;

	void EnemyItemDrop() override;
};

#endif // !_ITEMDROP_SWARMENEMY_H_

