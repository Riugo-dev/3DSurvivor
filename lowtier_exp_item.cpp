//********************************************************************************
//
// lowtier_exp_item.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************
#include "main.h"
#include <random>

#include "lowtier_exp_item.h"

LowTierExpItem::LowTierExpItem()
{
	

	m_Scale = { 1.0f , 1.0f , 1.0f };

	m_Shader = SHADER_BLINNPHONG;

	std::random_device rd;
	m_Exp = rd() % 30 + 5;
	m_ModelTag = LOWTIER_EXP;

	m_Radius = 0.31f;
}

LowTierExpItem::~LowTierExpItem()
{
	
}
