//********************************************************************************
//
// midtier_exp_item.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#ifndef _MIDTIER_EXP_ITEM
#define _MIDTIER_EXP_ITEM

#include "exp_item.h"

class MidTierExpItem : public ExpItem
{
public:
	MidTierExpItem() = default;
	~MidTierExpItem() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};


#endif // !_MIDTIER_EXP_ITEM

