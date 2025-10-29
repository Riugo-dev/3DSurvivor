//********************************************************************************
//
// vacuum_item.h[‰ñŽûƒAƒCƒeƒ€]
//
//															Author :Riugo Honda
//															Date   :2025/10/24
//********************************************************************************

#ifndef _VACUUM_ITEM
#define _VACUUM_ITEM

#include "exp_item.h"

class VacuumItem : public ExpItem
{
public:
	VacuumItem();
	~VacuumItem() override;

	void Update() override;
};


#endif // !_VACUUM_ITEM
