//********************************************************************************
//
// bullet.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/06/04
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/04
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "camera.h"
#include "modelRenderer.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "input.h"
#include <vector>
#include "lowtier_exp_item.h"

#include "bullet.h"

//********************************************************************************
//関数
//********************************************************************************
Bullet::Bullet(Vector3 size, Vector3 position)
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\bullet.obj");

	m_Scale = size;

	//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
	Camera* p_camera =Manager::GetScene()->GetGameObject<Camera>();
	Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

	m_Position = player->GetPosition() + (p_camera->GetFoward() * 0.05f);
	m_Position.m_y += 0.5f;

	m_Velocity = p_camera->GetFoward() * 0.5f;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

}

Bullet::~Bullet()
{
	delete m_pModelRenderer;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Init(Input* p_input)
{
	//m_pInput = p_input;
}

void Bullet::Uninit()
{

}

void Bullet::Update()
{
	m_Position += m_Velocity;

	////エルミート曲線
	//m_Time += 0.02;
	//
	//m_Position = m_StartPosition * (2.0f * m_Time * m_Time * m_Time - 3.0f * m_Time * m_Time + 1.0f) 
	//	+ m_EndPosition * (-2.0f * m_Time * m_Time * m_Time + 3.0f * m_Time * m_Time)
	//	+ m_StartVector *(m_Time * m_Time * m_Time - 2.0f * m_Time * m_Time + m_Time)
	//	+ m_EndVector * (m_Time * m_Time * m_Time - m_Time * m_Time);

	Manager::GetScene()->AddGameObject<Explosion>(2)->SetPosition(m_Position);//重くなりすぎる

	/*Enemy* p_enemy = Manager::GetGameObject<Enemy>();

	Vector3 d = p_enemy->GetPosition() - m_Position;
	float length = d.length();
	if (length < 1.0f)
	{
		m_IsDestroy = true;
		p_enemy->SetDestroy(true);
	}*/

	//敵との衝突判定
	std::vector<Enemy*> p_enemys = Manager::GetScene()->GetGameObjects<Enemy>();//auto enemies = でも大丈夫

	for (auto itr : p_enemys)
	{
		Vector3 d = itr->GetPosition() - m_Position;
		float length = d.length();
		if (length < 1.0f)
		{
			Manager::GetScene()->AddGameObject<Explosion>(2)->SetPosition(itr->GetPosition() + Vector3(0.0f , 1.0f , 0.0f));

			Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition(itr->GetPosition() + Vector3(0.0f, 1.0f, 0.0f));

			m_IsDestroy = true;
			itr->SetDestroy(true);
		}
	}

	

	m_LivingFrame++;

	if (m_LivingFrame >= 60)
	{
		m_IsDestroy = true;
	}
	//Camera* p_camera = Manager::GetGameObject<Camera>();

	//if (m_pInput->GetKeyPress(KK_A))
	//{
	//	//m_Position += Vector3(-1.0f, 0.0f, 0.0f);
	//	m_Position += -p_camera->GetRight() * 0.1f;
	//}

	//if (m_pInput->GetKeyPress(KK_D))
	//{
	//	//m_Position += Vector3(1.0f, 0.0f, 0.0f);
	//	m_Position += p_camera->GetRight() * 0.1f;
	//}

	//if (m_pInput->GetKeyPress(KK_W))
	//{
	//	//m_Position += Vector3(0.0f, 0.0f, 1.0f);
	//	m_Position += p_camera->GetFoward() * 0.1f;
	//}

	//if (m_pInput->GetKeyPress(KK_S))
	//{
	//	//m_Position += Vector3(0.0f, 0.0f, -1.0f);
	//	m_Position += -p_camera->GetFoward() * 0.1f;
	//}

	//Vector3 rotation = p_camera->GetRotation();
	//m_Rotation.m_y = rotation.m_y;

	/*m_Rotation.m_x += 0.1f;
	m_Rotation.m_y += 0.1f;*/
	//m_Rotation.z += 0.1f;

	//updateposition();
}

void Bullet::Draw()
{


	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//平行移動行列の作成（表示座標を決める）
	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

	//回転行列（Z回転）行列の作成
	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y + XM_PI, m_Rotation.m_z);

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

	m_pModelRenderer->Draw();
}

