//********************************************************************************
//
// title.h[titleƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/06/25
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/25
//********************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"

class Input;


class Title :public Scene
{
private:
	Input* m_Input;
public:

	void Init(Input*) override;		//‰Šú‰»
	void Uninit() override; 
	void Update() override;
};

#endif // !_TITLE_H_
