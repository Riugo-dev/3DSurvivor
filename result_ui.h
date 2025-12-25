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

enum State
{
	RESULT = 0,
	RANKING,
};

class ResultUI :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TextureResultScore;//文字
	ID3D11ShaderResourceView* m_TextureResultEXPBonus;//文字
	ID3D11ShaderResourceView* m_TextureResultTotalScore;//文字
	ID3D11ShaderResourceView* m_TextureNumbers;//文字
	ID3D11ShaderResourceView* m_TextureBG;//背景画
	ID3D11ShaderResourceView* m_RankText[5];//背景画

	XMFLOAT3 m_VertexPosition[4] = {};

	int m_Score;
	int m_EXPBonus;
	int m_TotalScore;
	int m_Ranking[5];
	float m_Height;
	bool m_IsRising;
	State m_State = RESULT;
public:
	ResultUI();
	~ResultUI() override;

	void Init() override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override;


	void SetScore(int score) { m_Score = score; }
	void SetBonusScore(int bonus) { m_EXPBonus = bonus; }
	void CalcTotal() { m_TotalScore = m_Score + m_EXPBonus; }
	int GetTotal() { return m_TotalScore; }

	void SetState(State state);
	State GetState() { return m_State; }
	bool GetIsRising() { return m_IsRising; }
private:
	void drawnumbers();
	void drawscore();
	void drawbonus();
	void drawtotal();
	void drawbg();
	void drawranks();
	void drawranknumbers();
};

#endif // !_RESULT_UI_H_
