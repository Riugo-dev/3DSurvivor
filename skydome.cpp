//********************************************************************************
//
// skydome.cpp[空]
//
//															Author :Riugo Honda
//															Date   :2025/06/11
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/14
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "modelRenderer.h"
#include "shader_manager.h"
#include "player.h"

#include "skydome.h"

//********************************************************************************
//関数
//********************************************************************************
SkyDome::SkyDome(Vector3 size, Vector3 position)
{
	/*m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\sky.obj");*/

	m_ModelTag = SKYDOME;

	m_Scale = size;

}

SkyDome::~SkyDome()
{
	
}

void SkyDome::Init()
{
	//m_pInput = p_input;
}

void SkyDome::Uninit()
{

}

void SkyDome::Update()
{
	//m_Rotation.z += 0.001;
	
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	m_Position = p_player->GetPosition();


}

void SkyDome::Draw()
{


	ModelManager::SetShaders(m_ModelTag, SHADER_UNLITTEXT);


	//平行移動行列の作成（表示座標を決める）
	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	//回転行列（Z回転）行列の作成
	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
	XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
	XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

	Renderer::SetWorldMatrix(WorldMatrix);

	//マテリアル設定
	MATERIAL material{};
	material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
	material.TextureEnable = false;
	Renderer::SetMaterial(material);

	//m_pModelRenderer->Draw();
	ModelManager::ModelDraw(m_ModelTag);
}


