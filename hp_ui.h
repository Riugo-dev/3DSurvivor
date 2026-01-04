//********************************************************************************
//
// score.h[スコア表示]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#ifndef _HP_UI_H_
#define _HP_UI_H_

#include "gameobject.h"


#define PLAYER_HP_MAX (3)

class HPUI : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_WorldBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TextureHP;//文字
	ID3D11ShaderResourceView* m_TextureHeart;//ハートの絵
	ID3D11ShaderResourceView* m_TextureCase;//ハートの空絵

	XMFLOAT3 m_VertexPosition[4] = {};

	int m_HP;
public:
	HPUI();
	~HPUI() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SubtractHP(int hp = 1);

	void AddHP(int hp = 1) 
	{ 
		if (m_HP >= PLAYER_HP_MAX) 
		{ 
			m_HP = PLAYER_HP_MAX; 
			return;
		}
		m_HP += hp; 
	}
	int GetHP() { return m_HP; }
private:
	void drawzerohp();
	void drawonehp();
	void drawtwohp();
	void drawthreehp();
	void drawhpword();
};

#endif // !_HP_UI_H_
