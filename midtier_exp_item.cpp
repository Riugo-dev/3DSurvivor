//********************************************************************************
//
// midtier_exp_item.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************

#include <random>

#include "midtier_exp_item.h"

MidTierExpItem::MidTierExpItem()
{
	

	m_Scale = { 1.0f , 1.0f , 1.0f };

	m_Shader = SHADER_BLINNPHONG;

	std::random_device rd;
	m_Exp = rd() % 60 + 21;
	m_ModelTag = MIDTIER_EXP;
}

MidTierExpItem::~MidTierExpItem()
{

}
