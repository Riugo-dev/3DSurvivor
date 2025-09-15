//********************************************************************************
//
// result_ui.h[[ポーズ画面表示]
//
//															Author :Riugo Honda
//															Date   :2025/09/15
//********************************************************************************
#ifndef _RESULT_UI_H_
#define _RESULT_UI_H_

#include "gameobject.h"

class ResultUI :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_VertexBufferResultUI;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TextureResultScore;//文字
	ID3D11ShaderResourceView* m_TextureResultEXPBonus;//文字
	ID3D11ShaderResourceView* m_TextureResultTotalScore;//文字
	ID3D11ShaderResourceView* m_TextureNumbers;//文字
	ID3D11ShaderResourceView* m_TextureBG;//背景画

	XMFLOAT3 m_VertexPosition[4] = {};

	int m_Score;
	int m_EXPBonus;
	int m_TotalScore;
public:
	ResultUI();
	~ResultUI();

	void Init(Input*) override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override;


	void SetScore(int score) { m_Score = score; }
	void SetBonusScore(int bonus) { m_EXPBonus = bonus; }
	void CalcTotal() { m_TotalScore = m_Score + m_EXPBonus; }
private:
	void drawnumbers();
	void drawscore();
	void drawbonus();
	void drawtotal();
	void drawbg();
};

#endif // !_RESULT_UI_H_
