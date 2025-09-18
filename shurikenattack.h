//********************************************************************************
//
// shurikenattack.h[ãÖçUåÇÇÃä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#ifndef _SHURIKENATTACK_H_
#define _SHURIKENATTACK_H_

#include "gameobject.h"



class ShurikenAttack :public GameObject
{
private:
	AttackLevel m_AttackLevel;
	int m_FrameCount;

public:
	ShurikenAttack();
	~ShurikenAttack() override {};

	void Init(Input*) override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override {};

	AttackLevel GetLevel() { return m_AttackLevel; }
	void SetLevel(AttackLevel level) { m_AttackLevel = level; }
	void SetToNextLevel();
};

#endif // !_SHURIKENATTACK_H_
