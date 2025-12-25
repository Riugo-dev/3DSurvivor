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


class BulletAttack:public GameObject
{
private:
	AttackLevel m_AttackLevel;
	int m_FrameCount;

public:
	BulletAttack();
	~BulletAttack() override {};

	void Init() override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override {};

	AttackLevel GetLevel() { return m_AttackLevel; }
	void SetLevel(AttackLevel level) { m_AttackLevel = level; }
	void SetToNextLevel();
};

#endif // !_BULLETATTACK_H_
