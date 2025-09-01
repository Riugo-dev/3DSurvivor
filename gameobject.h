//********************************************************************************
//
// ゲームオブジェクトヘッダー[gameobject.h]
//
//															Author :Riugo Honda
//															Date   :2025/05/21
// -------------------------------------------------------------------------------
//															Last Edited:2025/05/21
//********************************************************************************
#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

class Input;

class GameObject
{
private:

protected:
	Vector3 m_Position = {0.0f , 0.0f , 0.0f};
	Vector3 m_Rotation = { 0.0f , 0.0f , 0.0f };
	Vector3 m_Scale = { 1.0f , 1.0f ,1.0f };
	bool m_IsDestroy = false;

	Input* m_pInput;
public:
	virtual void Init(Input*) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	Vector3 GetPosition() { return m_Position; }
	void SetPosition(Vector3 pos) { m_Position = pos; }

	Vector3 GetRotation() { return m_Rotation; }
	void SetRotation(Vector3 rot) { m_Rotation = rot; }

	Vector3 GetScale() { return m_Scale; }
	void SetScale(Vector3 scale) { m_Scale = scale; }

	bool GetDestroy() { return m_IsDestroy; }
	void SetDestroy(bool flag) { m_IsDestroy = flag; }

	Vector3 GetRight()
	{
		XMMATRIX matrix;
		matrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

		Vector3 right;
		XMStoreFloat3((XMFLOAT3*)&right, matrix.r[0]);

		return right;
	}

	Vector3 GetFoward()
	{
		XMMATRIX matrix;
		matrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

		Vector3 foward;
		XMStoreFloat3((XMFLOAT3*)&foward, matrix.r[2]);

		return foward;
	}

	float GetDistanceFromCamera(Vector3 Position)
	{
		return (m_Position - Position).length();
	}
};


#endif // !_GAMEOBJECT_H_
