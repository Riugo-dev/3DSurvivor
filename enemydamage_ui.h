//********************************************************************************
//
// enemydamage_ui.h[敵ダメージUIクラス]
//
//															Author :Riugo Honda
//															Date   :2026/02/07
//********************************************************************************

#ifndef _ENEMYDAMAGE_UI_
#define _ENEMYDAMAGE_UI_

enum DamageUI
{
	DAMAGE_1,
	DAMAGE_60,
	DAMAGE_360,
	DAMAGE_420,
	DAMAGE_480,
	DAMAGE_540,
	DAMAGE_600,
};

class EnemyDamageUI
{
private:
	static EnemyDamageUI* m_pMySelf;

	struct DamageUIInfo
	{
		ID3D11ShaderResourceView* Texture;
		ID3D11Buffer* InstanceBuffer;
		std::vector<InstanceData> m_Sendingdata;
	};

	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;
	ID3D11Buffer* m_pCameraBuffer = nullptr;

	std::unordered_map<DamageUI, DamageUIInfo> map_DamageUIs;

public:
	static EnemyDamageUI* GetInstance();

	void DestroyInstance();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SpawnDamageUI(DamageUI , Vector3);

private:
	EnemyDamageUI() {}
	~EnemyDamageUI() {}


};

#endif // !_ENEMYDAMAGE_UI_
