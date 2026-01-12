//********************************************************************************
//
// heal_item.h[‰ñ•œƒAƒCƒeƒ€]
//
//															Author :Riugo Honda
//															Date   :2025/10/24
//********************************************************************************

#ifndef _HEAL_ITEM
#define _HEAL_ITEM

#include "exp_item.h"

class HealItem : public ExpItem
{
public:
	HealItem() = default;
	~HealItem() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};


#endif // !_HEAL_ITEM
