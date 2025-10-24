//********************************************************************************
//
// attackbase_slipdamage.h[スリップダメージ攻撃の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#ifndef  _ATTACKBASE_SLIPDAMAGE_H_
#define  _ATTACKBASE_SLIPDAMAGE_H_

#include "attackbase.h"

class BaseAttackSlipDamage : public BaseAttack
{
private:
	class FireParticle* m_pFire = nullptr;
	bool m_BombExplode;
public:
	BaseAttackSlipDamage();
	~BaseAttackSlipDamage();

	void Update() override;
	void Draw() override;
	

};

#endif // ! _ATTACKBASE_SLIPDAMAGE_H_
