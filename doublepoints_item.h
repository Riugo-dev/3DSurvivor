//********************************************************************************
//
// doublepoints_item.h[二倍スコアアイテム]
//
//															Author :Riugo Honda
//															Date   :2026/02/15
//********************************************************************************

#ifndef _DOUBLEPOINTS_ITEM_H_
#define _DOUBLEPOINTS_ITEM_H_

#include "exp_item.h"

class DoublePointsItem : public ExpItem
{
public:
	DoublePointsItem() = default;
	~DoublePointsItem() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

#endif // !_DOUBLEPOINTS_ITEM_H_
