//********************************************************************************
//
// bombattack.h[îöíeçUåÇÇÃä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/10/23
//********************************************************************************
#ifndef _BOMBATTACK_H_
#define _BOMBATTACK_H_

#include "gameobject.h"


class BombAttack :public GameObject
{
private:
	AttackLevel m_AttackLevel;
	int m_FrameCount;

public:
	BombAttack();
	~BombAttack() override {};

	void Init(Input*) override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override {};

	AttackLevel GetLevel() { return m_AttackLevel; }
	void SetLevel(AttackLevel level) { m_AttackLevel = level; }
	void SetToNextLevel();
};

#endif // !_BOMBATTACK_H_

