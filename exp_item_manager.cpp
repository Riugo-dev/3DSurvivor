//********************************************************************************
//
// exp_item_manager.cpp[経験値アイテム管理クラス]
//
//															Author :Riugo Honda
//															Date   :2026/01/31
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "exp_item.h"
#include <random>
#include <cmath>
#include <vector>

#include "exp_item_manager.h"

//********************************************************************************
//マクロ定義
//********************************************************************************
#define EXPITEM_MAX_NUM (1000)	//かなりの量が落ちるのでエネミーより多めに設定

//********************************************************************************
//グローバル変数
//********************************************************************************
ExpItemManager* ExpItemManager::m_pMySelf;

//********************************************************************************
//関数
//********************************************************************************

//呼び出し用の関数（初期化処理付き）
ExpItemManager* ExpItemManager::GetInstance()
{
	if (!m_pMySelf)
	{
		m_pMySelf = new ExpItemManager;

		m_pMySelf->Init();
	}

	return m_pMySelf;
}

//自身の破壊及び終了処理
void ExpItemManager::DestroySelf()
{
	m_pMySelf->Uninit();
	delete m_pMySelf;
	m_pMySelf = nullptr;
}

//バッファの作成
void ExpItemManager::Init()
{
	for (int tag = LOWTIER_EXP; tag < ITEM_HEAL; tag++)
	{
		map_ExpItems[(ModelTags)tag] = ExpItemInstanceGroup();

		auto& inst = map_ExpItems[(ModelTags)tag];

		//経験値アイテムの最大保持数確保・・・後程制限を追加
		inst.ExpItems.reserve(EXPITEM_MAX_NUM);
		inst.SendingData.reserve(EXPITEM_MAX_NUM);

		//全て同じシェーダーだからここで定義
		inst.ShaderInfo = SHADER_INSTANCE_BLINNPHONG;

		//ここからバッファの作成
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DYNAMIC;//書き込み可能に
		desc.ByteWidth = sizeof(InstanceData) * EXPITEM_MAX_NUM;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;//書き込み可能に

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &inst.InstanceBuffer);

		assert(inst.InstanceBuffer != nullptr);//バッファ作成失敗してないかのチェック
	}
}

//ポインターの消去
void ExpItemManager::Uninit()
{
	for (auto& itr : map_ExpItems)
	{
		ExpItemInstanceGroup& inst = itr.second;

		inst.InstanceBuffer->Release();
		inst.ExpItems.clear();
	}
}

void ExpItemManager::AddExpItem(ExpItem* item)
{
	//経験値アイテムの情報を登録
	for (auto& itr : map_ExpItems)
	{
		auto tag = itr.first;
		ExpItemInstanceGroup& inst = itr.second;

		if (tag == item->GetModelTag())
		{
			inst.ExpItems.push_back(item);
		}
	}
}

void ExpItemManager::Update()
{
	for (auto& itr : map_ExpItems)
	{
		ExpItemInstanceGroup& inst = itr.second;

		UpdateInstanceBuffer(inst);
	}
}

void ExpItemManager::Draw()
{
	for (auto& itr : map_ExpItems)
	{
		ModelTags tag = itr.first;
		ExpItemInstanceGroup& inst = itr.second;

		//インスタンスが無ければ処理を飛ばす
		if (inst.SendingData.empty()) continue;

		assert(!inst.SendingData.empty());


		{//通常のインスタンス描画
			ModelManager::SetShaders(tag, inst.ShaderInfo);

			//残りのドロー処理をここに書く
			UINT strides[2] = { sizeof(VERTEX_3D) , sizeof(InstanceData) };
			UINT offsets[2] = { 0 , 0 };

			MODEL* model = ModelManager::GetModelRenderers(tag)->GetModel();

			assert(model->VertexBuffer != nullptr);
			assert(model->IndexBuffer != nullptr);

			ID3D11Buffer* buffers[2]{ model->VertexBuffer , inst.InstanceBuffer };

			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 2, buffers, strides, offsets);



			Renderer::GetDeviceContext()->IASetIndexBuffer(model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


			for (int i = 0; i < model->SubsetNum; i++)
			{
				assert(model->SubsetArray[i].IndexNum > 0);

				//マテリアルの固定
				Renderer::SetMaterial(model->SubsetArray[i].Material.Material);

				//実際の描画
				Renderer::GetDeviceContext()->DrawIndexedInstanced(model->SubsetArray[i].IndexNum, inst.SendingData.size(), model->SubsetArray[i].StartIndex, 0, 0);
			}
		}

		{//エッジのインスタンス描画
			ModelManager::SetShaders(tag, SHADER_INSTANCE_EDGE);

			//残りのドロー処理をここに書く
			UINT strides[2] = { sizeof(VERTEX_3D) , sizeof(InstanceData) };
			UINT offsets[2] = { 0 , 0 };

			Renderer::SetCullMode(D3D11_CULL_FRONT);

			MODEL* model = ModelManager::GetModelRenderers(tag)->GetModel();

			assert(model->VertexBuffer != nullptr);
			assert(model->IndexBuffer != nullptr);

			ID3D11Buffer* buffers[2]{ model->VertexBuffer , inst.InstanceBuffer };

			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 2, buffers, strides, offsets);

			Renderer::GetDeviceContext()->IASetIndexBuffer(model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			for (int i = 0; i < model->SubsetNum; i++)
			{
				assert(model->SubsetArray[i].IndexNum > 0);

				//マテリアルの固定
				Renderer::SetMaterial(model->SubsetArray[i].Material.Material);

				//実際の描画
				Renderer::GetDeviceContext()->DrawIndexedInstanced(model->SubsetArray[i].IndexNum, inst.SendingData.size(), model->SubsetArray[i].StartIndex, 0, 0);
			}

			Renderer::SetCullMode(D3D11_CULL_BACK);

		}
	}
}

//********************************************************************************
//プライベート関数
//********************************************************************************

void ExpItemManager::UpdateInstanceBuffer(ExpItemInstanceGroup& group)
{
	//もしアイテムが回収済みを消える予定なら消す
	group.ExpItems.erase
	(
		std::remove_if
		(
			group.ExpItems.begin(),
			group.ExpItems.end(),
			[](ExpItem* enemy)
			{
				return enemy == nullptr || enemy->GetDestroy();
			}
		),
		group.ExpItems.end()
	);

	group.SendingData.clear();

	for (auto* itr : group.ExpItems)
	{
		InstanceData inst{};
		inst.Position = { itr->GetPosition().x , itr->GetPosition().y , itr->GetPosition().z , 1.0f };
		inst.Rotation = { itr->GetRotation().x , itr->GetRotation().y , itr->GetRotation().z , 0.0f };
		inst.Scale = { itr->GetScale().x , itr->GetScale().y , itr->GetScale().z , 1.0f };

		group.SendingData.push_back(inst);
	}

	if (group.SendingData.empty()) return;

	D3D11_MAPPED_SUBRESOURCE mapped{};
	HRESULT hr = Renderer::GetDeviceContext()->Map(group.InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);//前のバッファのデータを破棄

	assert(SUCCEEDED(hr));

	memcpy(mapped.pData, group.SendingData.data(), sizeof(InstanceData) * group.SendingData.size());//新しいデータのバッファへの書き込み

	Renderer::GetDeviceContext()->Unmap(group.InstanceBuffer, 0);

	assert(!group.SendingData.empty());

}