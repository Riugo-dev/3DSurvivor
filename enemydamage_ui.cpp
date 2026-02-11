//********************************************************************************
//
// enemydamage_ui.h[敵ダメージUIクラス]
//
//															Author :Riugo Honda
//															Date   :2026/02/07
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"

#include <vector>
#include <unordered_map>

#include "enemydamage_ui.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
EnemyDamageUI* EnemyDamageUI::m_pMySelf;

#define DAMAGE_ONE_MAX (1000)
#define DAMAGE_OTHER_MAX (300)

//********************************************************************************
//関数
//********************************************************************************

EnemyDamageUI* EnemyDamageUI::GetInstance()
{
	if (!m_pMySelf)
	{
		m_pMySelf = new EnemyDamageUI;

		m_pMySelf->Init();
	}

	return m_pMySelf;
}

void EnemyDamageUI::DestroyInstance()
{
	if (!m_pMySelf)return;
	m_pMySelf->Uninit();
	delete m_pMySelf;
	m_pMySelf = nullptr;
}

void EnemyDamageUI::Init()
{
	createbuffers();
	createshaders();
}

void EnemyDamageUI::Uninit()
{

}

void EnemyDamageUI::Update()
{

}

void EnemyDamageUI::Draw()
{

}

void EnemyDamageUI::SpawnDamageUI(DamageUI damage, Vector3 pos)
{

}



//********************************************************************************
//プライベート関数
//********************************************************************************

void EnemyDamageUI::createbuffers()
{
	for (int tag = DAMAGE_1; tag < DAMAGE_MAX; tag++)
	{
		map_DamageUIs[(DamageUI)tag] = DamageUIInfo();

		auto& inst = map_DamageUIs[(DamageUI)tag];

		switch(tag)
		{
		case DAMAGE_1:
			inst.m_Sendingdata.reserve(DAMAGE_ONE_MAX);
			inst.m_DamageData.reserve(DAMAGE_ONE_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage1.png");
			break;
		case DAMAGE_60:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage60.png");
			break;
		case DAMAGE_300:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage300.png");
		case DAMAGE_360:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage360.png");
			break;
		case DAMAGE_420:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage420.png");
			break;
		case DAMAGE_480:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage480.png");
			break;
		case DAMAGE_540:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage540.png");
			break;
		case DAMAGE_600:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage600.png");
			break;
		}

		//インスタンスバッファの作成
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &inst.InstanceBuffer);

		{
			//VertexBufferの作成
			VERTEX_3D vertex[4];
			vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			D3D11_BUFFER_DESC desc{};
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(VERTEX_3D) * 4;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA srd{};
			srd.pSysMem = vertex;

			Renderer::GetDevice()->CreateBuffer(&desc, &srd, &inst.m_pVertexBuffer);
		}

	} 
}

void EnemyDamageUI::createshaders()
{
	Renderer::CreateInstanceVertexShader(&m_pVertexShader, &m_pInputLayout, "shader\\unlitTexInstancedVS.cso");
	Renderer::CreatePixelShader(&m_pPixelShader ,"shader\\unlitTexturePS.cso");
}

