//********************************************************************************
//
// camera.cpp[カメラ]
//
//															Author :Riugo Honda
//															Date   :2025/05/14
// -------------------------------------------------------------------------------
//															Last Edited:2025/09/14
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "scene.h"
#include "controller.h"

#include "camera.h"

#define CAMERA_LENGTH_TP_X	(0.0f)
#define CAMERA_LENGTH_TP_Y	(12.0f)
#define CAMERA_LENGTH_TP_Z	(-15.0f)

#define CAMERA_LENGTH_FP_X	(0.0f)
#define CAMERA_LENGTH_FP_Y	(2.0f)
#define CAMERA_LENGTH_FP_Z	(2.0f)

#define CAMERA_TARGET_FP_X	(0.0f)
#define CAMERA_TARGET_FP_Y	(2.0f)
#define CAMERA_TARGET_FP_Z	(10.0f)


//********************************************************************************
//関数
//********************************************************************************
Camera::Camera(Vector3 postion , Vector3 target ,int movementx, int movementy, Vector3 rotation)
{
	
	
	m_Position = postion;
	m_Target = target;

	m_Rotation = rotation;

	m_movement_x = movementx;
	m_movement_y = movementy;

	m_Mode = CAMERA_MODE_TP;

	IsRotating = false;
	//m_Shake = 0.0f;
	//m_ShakeTime = 0.0f;

	//m_CameraIndex = -1;



	//m_OldPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//m_Interpolation = 1.0f;//距離ではなく補間割合で計算
}

Camera::~Camera()
{
	
}

void Camera::Init(Input* input)
{
	m_pInput = input;
}

void Camera::Uninit()
{

}

void Camera::Update()
{
	if (m_Mode == CAMERA_MODE_TITLE)
	{
		m_Target = Vector3{ 0.0f , 1.0f ,0.0f };

		//カメラシェイク
		m_Target += m_ShakeVector * cosf(m_ShakeTime);
		m_ShakeTime += 1.0f;//揺らす速さ
		m_ShakeVector *= 0.9f;

		m_Position = { m_Target.m_x + (-sinf(m_Rotation.m_y) * 5.0f), m_Target.m_y + CAMERA_LENGTH_TP_Y , m_Target.m_z + (-cosf(m_Rotation.m_y) * 5.0f) };


		Renderer::SetCameraPosition(m_Position);

		return;
	}

	Controller* p_contorller = Manager::GetController();

	if (p_contorller->IsConnected())
	{
		if (p_contorller->Controller_RightStickIsLeft())
		{
			m_Rotation.m_y += -0.05f;
			IsRotating = true;
		}
		else if (p_contorller->Controller_RightStickIsRight())
		{
			m_Rotation.m_y += 0.05f;
			IsRotating = true;
		}
	}
	else
	{
		if (m_pInput->GetKeyPress(KK_LEFT))
		{
			m_Rotation.m_y += -0.05f;
			IsRotating = true;
		}
		else if (m_pInput->GetKeyPress(KK_RIGHT))
		{
			m_Rotation.m_y += 0.05f;
			IsRotating = true;
		}
	}
	/*else if (m_pInput->GetKeyPress(KK_RIGHTSHIFT))
	{
		m_Rotation.m_y = 0.0f;
		IsRotating = false;
	}*/


	if (m_pInput->GetKeyPress(KK_ENTER))
	{
		m_Position.m_z += 0.1f;
	}

	if (m_pInput->GetKeyTrigger(KK_D1))
	{
		m_Mode = CAMERA_MODE_TP;
	}
	else if (m_pInput->GetKeyTrigger(KK_D2))
	{
		m_Mode = CAMERA_MODE_FP;
	}

	if (m_Mode == CAMERA_MODE_TP)
	{
		Player* player = Manager::GetScene()->GetGameObject<Player>();

		if (player == nullptr) return;

		m_Target = player->GetPosition() + Vector3{ 0.0f , 1.0f ,0.0f };

		//カメラシェイク
		m_Target += m_ShakeVector * cosf(m_ShakeTime);
		m_ShakeTime += 1.0f;//揺らす速さ
		m_ShakeVector *= 0.9f;

		m_Position = { m_Target.m_x + (-sinf(m_Rotation.m_y) * 5.0f), m_Target.m_y + CAMERA_LENGTH_TP_Y , m_Target.m_z + (-cosf(m_Rotation.m_y) * 5.0f) };

		//m_Position = { -12.7 , 12.5 , -0.47 };

		/*if(!IsRotating)
		{
			m_Position = { m_Target.m_x + CAMERA_LENGTH_TP_X , m_Target.m_y + CAMERA_LENGTH_TP_Y , m_Target.m_z + CAMERA_LENGTH_TP_Z };
		}
		else 
		{
			m_Position = { m_Target.m_x + (-sinf(m_Rotation.m_y) * 5.0f), m_Target.m_y + CAMERA_LENGTH_TP_Y , m_Target.m_z + (-cosf(m_Rotation.m_y) * 5.0f) };
		}*/
	}
	else if (m_Mode == CAMERA_MODE_FP)
	{
		Player* player = Manager::GetScene()->GetGameObject<Player>();

		if (player == nullptr) return;

		m_Position = { player->GetPosition().m_x, player->GetPosition().m_y + CAMERA_LENGTH_FP_Y ,player->GetPosition().m_z };

		//カメラシェイク
		m_Target += m_ShakeVector * cosf(m_ShakeTime);
		m_ShakeTime += 1.0f;//揺らす速さ
		m_ShakeVector *= 0.9f;

		/*m_Target = player->GetPosition() + Vector3{ CAMERA_TARGET_FP_X + (sinf(m_Rotation.m_y)* 5.0f), CAMERA_TARGET_FP_Y , CAMERA_TARGET_FP_Z + (cosf(m_Rotation.m_y) * 5.0f) };*/
		m_Target = m_Position + Vector3{(sinf(m_Rotation.m_y) * 5.0f), 0.0f,(cosf(m_Rotation.m_y) * 5.0f)};


		//m_Position = { player->GetPosition().m_x + CAMERA_LENGTH_FP_X , player->GetPosition().m_y + CAMERA_LENGTH_FP_Y , player->GetPosition().m_z + CAMERA_LENGTH_FP_Z };
		
	}

	Renderer::SetCameraPosition(m_Position);

	//XMFLOAT3 target = GetBallPosition();

	//m_Target.x += (target.x - m_Target.x) * 0.05f;
	//m_Target.y += (target.y - m_Target.y) * 0.05f;
	//m_Target.z += (target.z - m_Target.z) * 0.05f;

	////カメラのシェイク
	//m_Target.y += m_Shake * cosf(m_ShakeTime);
	//m_ShakeTime += XM_2PI / 3.0f; //（シェイクの速さ決め）
	//m_Shake *= 0.9f;			  //シェイクの長さ決め

	//if (Keyboard_IsKeyTrigger(KK_D1))
	//{
	//	m_CameraIndex = -1;
	//	m_Interpolation = 0.0f;
	//	m_OldPosition = m_Position;
	//}
	//if (Keyboard_IsKeyTrigger(KK_D2))
	//{
	//	m_CameraIndex = 0;
	//	m_Interpolation = 0.0f;
	//	m_OldPosition = m_Position;
	//}
	//if (Keyboard_IsKeyTrigger(KK_D3))
	//{
	//	m_CameraIndex = 1;
	//	m_Interpolation = 0.0f;
	//	m_OldPosition = m_Position;
	//}
	//if (Keyboard_IsKeyTrigger(KK_D4))
	//{
	//	m_CameraIndex = 2;
	//	m_Interpolation = 0.0f;
	//	m_OldPosition = m_Position;
	//}

	////補間

	//if (m_CameraIndex == -1)
	//{
	//	//縦回転込みのカメラ回転制御
	//	m_Position.x = m_Target.x + sinf(m_Rotation.y) * cosf(m_Rotation.x) * 12.0f;
	//	m_Position.y = m_Target.y + sinf(m_Rotation.x) * 12.0f;
	//	m_Position.z = m_Target.z - cosf(m_Rotation.y) * cosf(m_Rotation.x) * 12.0f;
	//}
	//else
	//{

	//	float t = easeInOutSine(m_Interpolation);

	//	//補間(線形補間）
	//	m_Position.x = m_OldPosition.x * (1.0f - t) + m_CameraPosition[m_CameraIndex].x * t;
	//	m_Position.y = m_OldPosition.y * (1.0f - t) + m_CameraPosition[m_CameraIndex].y * t;
	//	m_Position.z = m_OldPosition.z * (1.0f - t) + m_CameraPosition[m_CameraIndex].z * t;

	//	//m_Position = m_CameraPosition[m_CameraIndex];
	//}

	//m_Interpolation += 0.01f;
	//if (m_Interpolation > 1.0f)
	//{
	//	m_Interpolation = 1.0f;
	//}

	//横回転のみのカメラ回転制御
	/*m_Position.x = m_Target.x +sinf(m_Rotation.y) * 12.0f;
	m_Position.z = m_Target.z -cosf(m_Rotation.y) * 12.0f;*/
}

void Camera::Draw()
{


	//カメラの見え方の設定(プロジェクションマトリクス（画角、アスペクト比））【カメラの設定】
	m_Projection = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//  XMMatrixPerspectiveFovLH(ここがズーム度, アスペクト比（必ずfloat）　, 1.0f, 1000.0f)

	Renderer::SetProjectionMatrix(m_Projection);


	//ビューマトリクス(カメラの位置、角度）【カメラの設定】
	//XMFLOAT3 pos = XMFLOAT3(a, b, c); //XMFLOAT3(0.0f, 2.0f, -3.0f); XMFLOAT (X , Y , Z)
	//XMFLOAT3 tgt = XMFLOAT3(d, e, f);  //XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);   //XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_View = XMMatrixLookAtLH(XMLoadFloat3((XMFLOAT3*) &m_Position), XMLoadFloat3((XMFLOAT3*) &m_Target), XMLoadFloat3(&up));//カメラの設定をするためのマトリックス　ココがかなり大事☆

	Renderer::SetViewMatrix(m_View);
}

void Camera::CameraShake(Vector3 shake)//引数が揺れの大きさ
{
	m_ShakeVector = shake;
	m_ShakeTime = 0.0f;

}

