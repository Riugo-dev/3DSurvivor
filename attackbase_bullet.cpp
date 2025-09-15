//********************************************************************************
//
// attackbase_bullet.h[‹…UŒ‚‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************

#include "attackbase_bullet.h"

BaseAttackBullet::BaseAttackBullet()
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\bullet.obj");

	m_Scale = { 1.0f , 1.0f ,1.0f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\pixelLightingBlinnPhongVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\pixelLightingBlinnPhongPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderEdge, &m_VertexLayout, "shader\\ToonVSEdge.cso");

	Renderer::CreatePixelShader(&m_PixelShaderEdge, "shader\\ToonPSEdge.cso");

	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };

	m_FrameCount = 0;
	m_LivingFrames = 0;
	m_Strength = 1;
}

BaseAttackBullet::~BaseAttackBullet()
{
	delete m_pModelRenderer;
	m_pModelRenderer = nullptr;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexShaderEdge->Release();
	m_PixelShaderEdge->Release();
}

void BaseAttackBullet::Update()
{
	m_Position += m_Velocity;

	if (m_FrameCount >= m_LivingFrames)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}
