//********************************************************************************
//
// hightier_exp_item.cpp[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#include	<random>

#include "hightier_exp_item.h"

HighTierExpItem::HighTierExpItem()
{
	

	m_Scale = { 1.0f , 1.0f , 1.0f };

	m_Shader = SHADER_BLINNPHONG;

	std::random_device rd;
	m_Exp = rd() % 100 + 51;
	m_ModelTag = HIGHTIER_EXP;
}

HighTierExpItem::~HighTierExpItem()
{
	
}
