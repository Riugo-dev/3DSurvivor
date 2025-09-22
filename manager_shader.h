//********************************************************************************
//
// manager_shader.h[音声エフェクトマネージャー]
//
//															Author :Riugo Honda
//															Date   :2025/09/22
//********************************************************************************

#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include "main.h"
#include <unordered_map>
#include <memory>

typedef enum
{
	SHADER_NONE = -1,
	SHADER_UNLITTEXT,
	SHADER_TOON,
	SHADER_BLINNPHONG,
	SHADER_TOONEDGE,
	SHADER_TOON_TWO,
	SAHDER_DIRECTIONLIGHTING,

	SHADER_MAX,
}Shader;

class ShaderPointers
{
private:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pVertexLayout;
public:
	ShaderPointers();
	~ShaderPointers();


	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader;}
	ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }
	ID3D11InputLayout* GetVertexLayout() { return m_pVertexLayout;}

	void SetShaderPointers(ID3D11VertexShader* vs, ID3D11PixelShader* ps, ID3D11InputLayout* vl);
};

class ShaderManager
{
private:
	std::unordered_map<Shader, ShaderPointers*> m_pShaderPointers;

public:
	ShaderManager();
	~ShaderManager();

	ShaderPointers* GetShaderPointers(Shader);
};

#endif // !_SHADER_MANAGER_H_
