#ifndef _MODEL_RENDERER_H_
#define _MODEL_RENDERER_H_

#include "renderer.h"
#include "component.h"
#include <string>
#include <unordered_map>

// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView* Texture;

};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL_OBJ
{
	VERTEX_3D* VertexArray;
	unsigned int	VertexNum;

	unsigned int* IndexArray;
	unsigned int	IndexNum;

	SUBSET* SubsetArray;
	unsigned int	SubsetNum;
};

struct MODEL
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	unsigned int VertexNum;
	SUBSET* SubsetArray;
	unsigned int	SubsetNum;
};



class ModelRenderer : public Component
{
private:

	static std::unordered_map<std::string, MODEL*> m_ModelPool;

	static void LoadModel(const char* FileName, MODEL* Model);
	static void LoadObj(const char* FileName, MODEL_OBJ* ModelObj);
	static void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);

	MODEL* m_Model{};

public:

	static void Preload(const char* FileName);
	static void UnloadAll();


	using Component::Component;

	void Load(const char* FileName);
	void Draw() override;
	void DrawInstanced(int, ID3D11ShaderResourceView*);

};

#endif // !_MODEL_RENDERER_H_


