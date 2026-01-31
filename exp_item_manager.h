//********************************************************************************
//
// exp_item_manager.h[経験値アイテム管理クラス]
//
//															Author :Riugo Honda
//															Date   :2026/01/31
//********************************************************************************

#ifndef _EXP_ITEM_MANAGER_
#define _EXP_ITEM_MANAGER_

#include "shader_manager.h"
#include "model_manager.h"
#include <vector>

class ExpItemManager
{
private:
	static ExpItemManager* m_pMySelf;

	struct ExpItemInstanceGroup
	{
		Shader ShaderInfo;
		std::vector<class ExpItem*> ExpItems;
		std::vector<InstanceData> SendingData;
		ID3D11Buffer* InstanceBuffer = nullptr;
	};

	std::unordered_map<ModelTags, ExpItemInstanceGroup> map_ExpItems;

public:
	static ExpItemManager* GetInstance();
	static void DestroySelf();

	void Init();
	void Uninit();

	void AddExpItem(ExpItem*);
	
	void Update();
	void Draw();

private:
	//シングルトン設計のため隠ぺい
	ExpItemManager() {}
	~ExpItemManager() {}

	void UpdateInstanceBuffer(ExpItemInstanceGroup&);
};

#endif // !_EXP_ITEM_MANAGER_
