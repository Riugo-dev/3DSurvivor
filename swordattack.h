//********************************************************************************
//
// swordattack.h[ãÖçUåÇÇÃä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#ifndef _SWORDATTACK_H_
#define _SWORDATTACK_H_

#include "gameobject.h"



class SwordAttack :public GameObject
{
private:
	AttackLevel m_AttackLevel;
	int m_FrameCount;

public:
	SwordAttack();
	~SwordAttack()override {};

	void Init() override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override {};

	AttackLevel GetLevel() { return m_AttackLevel; }
	void SetLevel(AttackLevel level) { m_AttackLevel = level; }
	void SetToNextLevel();

};

#endif // !_SWORDATTACK_H_
