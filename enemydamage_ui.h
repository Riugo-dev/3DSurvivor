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
	DAMAGE_300,
	DAMAGE_360,
	DAMAGE_420,
	DAMAGE_480,
	DAMAGE_540,
	DAMAGE_600,

	DAMAGE_MAX,
};

class EnemyDamageUI
{
private:
	static EnemyDamageUI* m_pMySelf;

	struct DamageData
	{
		Vector3 Position;
		Vector3 Scale;
		Vector3 Rotation;
		int LifeCount;
		bool IsDestory;
		Vector3 velocity;
		int MaxLife;
	};

	struct DamageUIInfo
	{
		ID3D11ShaderResourceView* Texture;
		ID3D11Buffer* m_pVertexBuffer = nullptr;
		ID3D11Buffer* InstanceBuffer;
		std::vector<InstanceData> m_Sendingdata;
		std::vector<DamageData> m_DamageData;
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

	void SpawnDamageUI(int , Vector3, bool isboss = false);

private:
	EnemyDamageUI() {}
	~EnemyDamageUI() {}

	void createbuffers();
	void createshaders();
	void updateuis();
	void updateinstancebuffer();
	void destroyuis();
};

#endif // !_ENEMYDAMAGE_UI_
