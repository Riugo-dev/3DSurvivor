//********************************************************************************
//
// levelone_midboss.h[ƒŒƒxƒ‹‚P“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _LEVELONE_MIDBOSS_H_
#define _LEVELONE_MIDBOSS_H_

#include "midbossbase.h"

class LevelOneMidBoss : public BaseMidBoss
{
public:
	LevelOneMidBoss() = default;
	~LevelOneMidBoss() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void MidBossItemDrop() override;
};

#endif // !_LEVELONE_MIDBOSS_H_

