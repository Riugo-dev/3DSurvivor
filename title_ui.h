//********************************************************************************
//
// title_ui.h[[タイトル画面表示]
//
//															Author :Riugo Honda
//															Date   :2025/10/30
//********************************************************************************
#ifndef _TITLE_UI_H_
#define _TITLE_UI_H_

#include "gameobject.h"

class TitleUI :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TextureTitleButtonCon;//文字
	ID3D11ShaderResourceView* m_TextureTitleButtonKey;//文字
	ID3D11ShaderResourceView* m_TextureTitleBar;//文字
	ID3D11ShaderResourceView* m_TextureBG;//背景画

	XMFLOAT3 m_VertexPosition[4] = {};
public:
	TitleUI();
	~TitleUI() override;

	void Init(Input*) override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override;

private:
	void drawtitlebar();
	void drawbutton();
	void drawbg();
};

#endif // !_TITLE_UI_H_
