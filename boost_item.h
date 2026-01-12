//********************************************************************************
//
// boost_item.h[ダッシュアイテム]
//
//															Author :Riugo Honda
//															Date   :2025/10/29
//********************************************************************************

#ifndef _BOOST_ITEM
#define _BOOST_ITEM

#include "exp_item.h"

class BoostItem : public ExpItem
{
public:
	BoostItem() = default;
	~BoostItem() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};


#endif // !_BOOST_ITEM

