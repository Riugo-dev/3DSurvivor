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

#include "main.h"

class Input;
typedef enum
{
	ATT_LVNONE = 0,
	ATT_LV1,
	ATT_LV2,
	ATT_LV3,
	ATT_LV4,
	ATT_LVMAX,
}AttackLevel;

class GameObject
{
private:

protected:
	Vector3 m_Position = {0.0f , 0.0f , 0.0f};
	Vector3 m_Rotation = { 0.0f , 0.0f , 0.0f };
	Vector3 m_Scale = { 1.0f , 1.0f ,1.0f };
	bool m_IsDestroy = false;

	Input* m_pInput;
	float m_Radius;

public:

	virtual ~GameObject() = default;

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
		matrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vector3 right;
		XMStoreFloat3((XMFLOAT3*)&right, matrix.r[0]);

		return right;
	}

	Vector3 GetFoward()
	{
		XMMATRIX matrix;
		matrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vector3 foward;
		XMStoreFloat3((XMFLOAT3*)&foward, matrix.r[2]);

		return foward;
	}

	float GetDistanceFromCamera(Vector3 Position)
	{
		return (m_Position - Position).length();
	}

	float GetZ(Vector3 position, Vector3 foward)
	{
		Vector3 direction = m_Position - position;
		return Vector3::dot(direction, foward);
	}


	float GetRadius() { return m_Radius; }
	void SetRadius(float radius) { m_Radius = radius; }

	bool CircleCollider(Vector3 enemypos, float radius)
	{
		Vector3 vector = m_Position - enemypos;
		float length = vector.length();

		if (length < radius + m_Radius)
		{
			return true;
		}

		return false;
	}
};


#endif // !_GAMEOBJECT_H_
