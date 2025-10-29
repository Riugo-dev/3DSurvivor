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
	HealItem();
	~HealItem() override;

	void Update() override;
};


#endif // !_HEAL_ITEM
