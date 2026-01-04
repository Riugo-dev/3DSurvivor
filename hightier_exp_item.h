//********************************************************************************
//
// hightier_exp_item.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#ifndef _HIGHTIER_EXP_ITEM
#define _HIGHTIER_EXP_ITEM

#include "exp_item.h"

class HighTierExpItem : public ExpItem
{
public:
	HighTierExpItem() = default;
	~HighTierExpItem() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};


#endif // !_HIGHTIER_EXP_ITEM
