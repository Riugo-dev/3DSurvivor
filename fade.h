//********************************************************************************
//
// Fade.h[攻撃管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/15
//********************************************************************************
#ifndef _FADE_H_
#define _FADE_H_

#include "gameobject.h"

typedef enum
{
	FADE_NONE = -1,
	FADE_IN,
	FADE_OUT,
	FADE_FIN,
}FadeState;

class Fade :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TextureFade;//文字

	FadeState m_State;

	Vector3 m_color;
	float m_trans;
public:
	Fade();
	~Fade();

	void Init(Input* p_input) { m_pInput = p_input; }
	void Uninit() override {};
	void Update() override;
	void Draw() override;

	void SetFade(FadeState state)
	{ 
		m_State = state; 
		
		if (state == FADE_IN)
		{
			m_trans = 1.0f;
		}
		else if (state == FADE_OUT)
		{
			m_trans = 0.0f;
		}
	}
	FadeState GetFade() { return m_State; }

	void SetColor(Vector3 col) { m_color = col; }
	void SetTrans(float trans) { m_trans = trans; }
	float GetTrans() { return m_trans; }
private:
	void fadein();
	void fadeout();
};

#endif // !_FADE_H_
