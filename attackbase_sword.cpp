//********************************************************************************
//
// attackbase_sword.h[‹…UŒ‚‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#include "manager.h"
#include "scene.h"
#include "player.h"

#include "attackbase_sword.h"

BaseAttackSword::BaseAttackSword()
{
	/*m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\AttackTypeSword.obj");*/

	m_ModelTag = SWORD;

	m_Scale = { 1.0f , 1.0f ,1.0f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\pixelLightingBlinnPhongVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\pixelLightingBlinnPhongPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };
	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_FrameCount = 0;
	m_LivingFrames = 0;
	m_angle = 0.0f;
	m_rotationspeed = 1.0f;
}

BaseAttackSword::~BaseAttackSword()
{
	//delete m_pModelRenderer;
	//m_pModelRenderer = nullptr;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}

void BaseAttackSword::Update()
{
	float dt = 0.1f;

	m_Velocity.m_y += m_gravity * dt;
	m_Position += m_Velocity * dt;
	m_Rotation.m_z += 1.0f;

	if (m_Position.m_y <= -1.0f)
	{
		m_IsDestroy = true;
	}
}

void BaseAttackSword::SetSword(Vector3 vel, Vector3 pos, float angle)
{
	m_Velocity = vel;
	

	m_angle = angle;

	m_Position = pos;

}

