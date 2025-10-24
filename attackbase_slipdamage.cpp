//********************************************************************************
//
// attackbase_bullet.h[球攻撃の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#include "manager.h"
#include "scene.h"
#include "fire_particle.h"
#include "explosion_particle.h"

#include "attackbase_slipdamage.h"

BaseAttackSlipDamage::BaseAttackSlipDamage()
{
	m_ModelTag = BOMB;

	m_Scale = { 1.0f , 1.0f , 1.0f };

	m_Shader = SHADER_BLINNPHONG;

	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };

	m_Radius = 0.0f;

	m_Strength = 1;

	m_BombExplode = false;

	m_HP = 1000000;
}

BaseAttackSlipDamage::~BaseAttackSlipDamage()
{
	
}

void BaseAttackSlipDamage::Update()
{
	m_Position += m_Velocity;

	if (m_Position.m_y < 0.0f)
	{
		m_Velocity = { 0.0f , 0.0f , 0.0f };
		m_Position.m_y = 0.5f;

		ExplosionParticle* boom = Manager::GetScene()->AddGameObject<ExplosionParticle>(2);
		boom->SetPosition(m_Position);
		boom->SetScale(m_Scale/5);

		m_pFire = Manager::GetScene()->AddGameObject<FireParticle>(2);
		m_pFire->SetParticle(m_LivingFrames, m_Position, m_Radius);

		m_BombExplode = true;
	}


	if (m_pFire != nullptr)
	{
		if (m_FrameCount >= m_LivingFrames)
		{
			m_IsDestroy = true;
		}
		m_FrameCount++;
	}
}

void BaseAttackSlipDamage::Draw()
{
	if(!m_BombExplode)
	{//通常の描画

		ModelManager::SetShaders(m_ModelTag, m_Shader);

		//平行移動行列の作成（表示座標を決める）
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

		//回転行列（Z回転）行列の作成
		XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

		//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
		XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, m_Scale.m_z);

		//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
		XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
		material.TextureEnable = false;
		Renderer::SetMaterial(material);



		Renderer::SetWorldMatrix(WorldMatrix);

		ModelManager::ModelDraw(m_ModelTag);

	}
}

