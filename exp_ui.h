//********************************************************************************
//
// exp_ui.h[経験値バーUIクラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/29
//********************************************************************************
#ifndef _EXP_UI_H_
#define _EXP_UI_H_

#include "gameobject.h"

class EXPUI : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TextureExpBar;//文字
	ID3D11ShaderResourceView* m_TextureExpBarFrame;//ハートの絵

	float m_expinterpolation;
	float m_expbarwidth;
	float m_expbarpos;
	Vector3 m_color;
	bool m_IslvMax;
public:
	EXPUI();
	~EXPUI();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	void drawframe();
	void drawexpbar();
	void drawexpbarmax();
	void colorchange();
};


#endif // !_EXP_UI_H_
