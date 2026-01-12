//********************************************************************************
//
// midtier_exp_item.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/09/04
//********************************************************************************
#include "main.h"
#include <random>
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "manager_soundeffect.h"

#include "midtier_exp_item.h"

MidTierExpItem::~MidTierExpItem()
{

}

void MidTierExpItem::Init()
{

	m_Scale = { 1.0f , 1.0f , 1.0f };

	m_Shader = SHADER_BLINNPHONG;

	std::random_device rd;
	m_Exp = rd() % 60 + 21;
	m_ModelTag = MIDTIER_EXP;

	m_Radius = 0.31f;
}

void MidTierExpItem::Uninit()
{
}

void MidTierExpItem::Update()
{
	m_Rotation.y += 0.1f;

	Player* player = Manager::GetScene()->GetGameObject<Player>();

	if (m_IsGathering)
	{
		Vector3 to_player = player->GetPosition() - m_Position;

		to_player = to_player.normalized();

		m_Position += to_player * m_GatherSpeed;
	}

	if (CircleCollider(player->GetPosition(), player->GetRadius()))
	{
		//SoundEffectManager::PlaySE(SE_EXP);

		player->GivePlayerExp(m_Exp);
		Manager::GetSoundEffect()->PlaySE(SE_EXPGET);
		m_IsDestroy = true;
	}

	if (m_FrameCount > 3000 && !m_IsGathering)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}

void MidTierExpItem::Draw()
{
	{//通常の描画
		//入力レイアウト設定
		//Renderer::GetDeviceContext()->IASetInputLayout(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetVertexLayout());

		////シェーダ設定
		//Renderer::GetDeviceContext()->VSSetShader(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetVertexShader(), NULL, 0);
		//Renderer::GetDeviceContext()->PSSetShader(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetPixelShader(), NULL, 0);

		ModelManager::SetShaders(m_ModelTag, m_Shader);

		//平行移動行列の作成（表示座標を決める）
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		//回転行列（Z回転）行列の作成
		XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
		XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

		//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
		XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
		material.TextureEnable = false;
		Renderer::SetMaterial(material);



		Renderer::SetWorldMatrix(WorldMatrix);

		//m_pModelRenderer->Draw();

		ModelManager::ModelDraw(m_ModelTag);
	}


	{//輪郭線の描画
		//Renderer::GetDeviceContext()->IASetInputLayout(Manager::GetShaders()->GetShaderPointers(SHADER_TOONEDGE)->GetVertexLayout());

		////シェーダ設定
		//Renderer::GetDeviceContext()->VSSetShader(Manager::GetShaders()->GetShaderPointers(SHADER_TOONEDGE)->GetVertexShader(), NULL, 0);
		//Renderer::GetDeviceContext()->PSSetShader(Manager::GetShaders()->GetShaderPointers(SHADER_TOONEDGE)->GetPixelShader(), NULL, 0);

		ModelManager::SetShaders(m_ModelTag, SHADER_TOONEDGE);

		Renderer::SetCullMode(D3D11_CULL_FRONT);

		//描画
		//m_pModelRenderer->Draw();
		ModelManager::ModelDraw(m_ModelTag);

		Renderer::SetCullMode(D3D11_CULL_BACK);
	}
}
