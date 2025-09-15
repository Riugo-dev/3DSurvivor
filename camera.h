//********************************************************************************
//
// camera.h[ÉJÉÅÉâ]
//
//															Author :Riugo Honda
//															Date   :2025/05/14
// -------------------------------------------------------------------------------
//															Last Edited:2025/05/14
//********************************************************************************
#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "gameobject.h"

class Input;

typedef enum
{
	CAMERA_MODE_NONE = -1,

	CAMERA_MODE_FP,
	CAMERA_MODE_TP,

	CAMERA_MODE_MAX = -1,
}CameraMode;

class Camera:public GameObject
{
private:

	int m_movement_x;
	int m_movement_y;

	Input* m_pInput;

	XMMATRIX m_View;
	XMMATRIX m_Projection;

	Vector3 m_Target;

	CameraMode m_Mode;
	bool IsRotating;

public:
	Camera(Vector3 postion = { 0.0f , 2.0f , -10.0f }, Vector3 target = { 0.0f , 0.0f , 0.0f }, int movementx = 0, int movementy = 0, Vector3 rotation = { 0.0f , 0.0f , 0.0f });
	~Camera();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	XMMATRIX GetViewMatrix() { return m_View; }
	XMMATRIX GetProjectionMatrix() {return m_Projection;}

private:

};

#endif // !_CAMERA_H_

