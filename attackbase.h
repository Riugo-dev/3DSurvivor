//********************************************************************************
//
// attackbase.h[攻撃の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/012
//********************************************************************************
#ifndef _ATTACKBASE_H_
#define _ATTACKBASE_H_

#include "main.h"
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "model_manager.h"
#include "shader_manager.h"
#include <vector>




class BaseAttack : public GameObject
{
protected:
	Shader m_Shader;

	int m_HP;//攻撃事態のHP（貫通することを考慮して）
	Vector3 m_Velocity;
	int m_FrameCount;
	int m_LivingFrames;

	int m_Strength;//攻撃の威力

	ModelTags m_ModelTag;

public:
	virtual ~BaseAttack() = default;

	void Init(Input*)override {};
	void Uninit() override {};
	virtual void Update() = 0;

	//全て同じ処理でドローするのでここで一括で書く
	virtual void Draw()	override
	{
		{//通常の描画
			////入力レイアウト設定
			//Renderer::GetDeviceContext()->IASetInputLayout(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetVertexLayout());

			////シェーダ設定
			//Renderer::GetDeviceContext()->VSSetShader(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetVertexShader(), NULL, 0);
			//Renderer::GetDeviceContext()->PSSetShader(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetPixelShader(), NULL, 0);

			ModelManager::SetShaders(m_ModelTag, m_Shader);

			//Manager::GetShaders()->SetShaders(m_Shader);

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

			//m_pModelRenderer->Draw();
			ModelManager::ModelDraw(m_ModelTag);

		}

	}

	void SetAttackHP(int hp) { m_HP = hp; }
	int GetAttackHP() { return m_HP; }
	void SubtractHP(int damage = 1) { m_HP -= damage; }

	int GetStrength() { return m_Strength; }
	void SetStrength(int pow) { m_Strength = pow; }

	Vector3 GetVelocity() { return m_Velocity; }
	void SetVelocity(Vector3 vel) { m_Velocity = vel;}

	void SetLivingFrames(int frames) { m_LivingFrames = frames; }

};

#endif // !_ATTACKBASE_H_

