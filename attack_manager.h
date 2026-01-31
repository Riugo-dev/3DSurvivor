//********************************************************************************
//
// attack_manager.h[攻撃管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/15
//********************************************************************************

#ifndef _ATTACK_MANAGER_H_
#define _ATTACK_MANAGER_H_

#include "gameobject.h"

class AttackManager:public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TextureBG;//文字
	ID3D11ShaderResourceView* m_TextureWordBG;//文字
	ID3D11ShaderResourceView* m_TextureShuriken;//背景画
	ID3D11ShaderResourceView* m_TextureSword;//文字
	ID3D11ShaderResourceView* m_TextureBullet;//背景画
	ID3D11ShaderResourceView* m_TextureBomb;//背景画
	ID3D11ShaderResourceView* m_TexturePowerUp;//文字
	ID3D11ShaderResourceView* m_TextureLVMAX;//背景画
	ID3D11ShaderResourceView* m_TextureSelect;//選択のくくり


	int m_SelectNumber;
	float m_SlideAnimation;
public:
	AttackManager();
	~AttackManager() override;

	void Init() {};
	void Uninit() override {};
	void Update() override;
	void Draw() override;

private:
	void drawbg();
	void drawicon();
	void drawselect();
	void drawoption();
};


#endif // !_ATTACK_MANAGER_H_
