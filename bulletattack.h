//********************************************************************************
//
// bulletattack.h[ãÖçUåÇÇÃä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#ifndef _BULLETATTACK_H_
#define _BULLETATTACK_H_

#include "gameobject.h"

typedef enum
{
	ATT_LV1 = 1,
	ATT_LV2,
	ATT_LV3,
	ATT_LV4,
	ATT_LVMAX,
}AttackLevel;

class BulletAttack:public GameObject
{
private:
	AttackLevel m_AttackLevel;
	int m_FrameCount;

public:
	BulletAttack();
	~BulletAttack();

	void Init(Input*) override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override {};

	AttackLevel GetLevel() { return m_AttackLevel; }
	void SetLevel(AttackLevel level) { m_AttackLevel = level; }

};

#endif // !_BULLETATTACK_H_
