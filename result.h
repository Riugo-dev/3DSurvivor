//********************************************************************************
//
// enemybase.h[“G‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/15
//********************************************************************************

#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

class Input;

class Result : public Scene
{
private:
	Input* m_Input;
	int m_score;
	int m_bonus;
public:
	Result();

	void Init(Input*) override;		//‰Šú‰»
	void Update() override;
};

#endif // !_RESULT_H_
