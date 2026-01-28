//	manager_effekseer.cpp
//	
//	2025.11.13			大山凌太朗

#include "main.h"
#include "manager_effekseer.h"

namespace graphics {

	EffekseerManager* EffekseerManager::GetInstance()
	{
		static EffekseerManager instance;
		return &instance;
	}

	bool EffekseerManager::Init(ID3D11Device* device, ID3D11DeviceContext* context, int maxInstances)
	{
		m_Device = device;
		m_Context = context;

		m_Renderer = EffekseerRendererDX11::Renderer::Create(device, context, maxInstances);
		m_Manager = Effekseer::Manager::Create(maxInstances);

		// レンダラーの標準ローダー
		m_Manager->SetSpriteRenderer(m_Renderer->CreateSpriteRenderer());
		m_Manager->SetRibbonRenderer(m_Renderer->CreateRibbonRenderer());
		m_Manager->SetRingRenderer(m_Renderer->CreateRingRenderer());
		m_Manager->SetTrackRenderer(m_Renderer->CreateTrackRenderer());
		m_Manager->SetModelRenderer(m_Renderer->CreateModelRenderer());

		m_Manager->SetTextureLoader(m_Renderer->CreateTextureLoader());
		m_Manager->SetModelLoader(m_Renderer->CreateModelLoader());
		m_Manager->SetMaterialLoader(m_Renderer->CreateMaterialLoader());

		// ★CurveLoader は 1.70e には無いので不要！

		m_Manager->SetCoordinateSystem(Effekseer::CoordinateSystem::RH);

		return true;
	}

	void EffekseerManager::Update()
	{
		if (m_Manager != nullptr)
			m_Manager->Update();
	}

	void EffekseerManager::Terminate()
	{
		m_EffectCache.clear();
		m_Manager.Reset();
		m_Renderer.Reset();
	}

	void EffekseerManager::DrawAll()
	{
		if (m_Manager == nullptr || m_Renderer == nullptr) return;

		ID3D11DeviceContext* ctx = m_Context;
		if (!ctx) return;

		// --- ステートを保存 ---
		ID3D11BlendState* oldBlend = nullptr;
		FLOAT blendFactor[4];
		UINT sampleMask;
		ctx->OMGetBlendState(&oldBlend, blendFactor, &sampleMask);

		ID3D11DepthStencilState* oldDepth = nullptr;
		UINT stencilRef;
		ctx->OMGetDepthStencilState(&oldDepth, &stencilRef);

		ID3D11RasterizerState* oldRaster = nullptr;
		ctx->RSGetState(&oldRaster);

		// --- Effekseerの描画 ---
		m_Renderer->BeginRendering();
		m_Manager->Draw();
		m_Renderer->EndRendering();

		// --- ステートを元に戻す ---
		ctx->OMSetBlendState(oldBlend, blendFactor, sampleMask);
		ctx->OMSetDepthStencilState(oldDepth, stencilRef);
		ctx->RSSetState(oldRaster);

		SAFE_RELEASE(oldBlend);
		SAFE_RELEASE(oldDepth);
		SAFE_RELEASE(oldRaster);
	}

	static std::u16string ToUTF16(const std::string& str)
	{
		int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		std::wstring wstr(sizeNeeded, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], sizeNeeded);

		return std::u16string(wstr.begin(), wstr.end());
	}

	Effekseer::EffectRef EffekseerManager::LoadEffect(const std::string& fileName)
	{
		auto it = m_EffectCache.find(fileName);
		if (it != m_EffectCache.end())
			return it->second;

		std::u16string path = ToUTF16(fileName);
		auto effect = Effekseer::Effect::Create(m_Manager, path.c_str());

		if (effect != nullptr)
			m_EffectCache[fileName] = effect;

		return effect;
	}

	Effekseer::Handle EffekseerManager::PlayEffect(const std::string& name, const Effekseer::Vector3D& pos)
	{
		if (m_Manager == nullptr) return -1;

		auto effect = LoadEffect(name);
		if (effect == nullptr) return -1;

		return m_Manager->Play(effect, pos.X, pos.Y, pos.Z);
	}

	void EffekseerManager::StopEffect(Effekseer::Handle handle)
	{
		if (m_Manager != nullptr)
			m_Manager->StopEffect(handle);
	}

	void EffekseerManager::StopAllEffects()
	{

		if (m_Manager != nullptr)
		{
			m_Manager->StopAllEffects();
		}

	}

	void EffekseerManager::SetSpeed(Effekseer::Handle handle, float speed)
	{
		if (m_Manager != nullptr)
			m_Manager->SetSpeed(handle, speed);
	}

	void EffekseerManager::SetColor(Effekseer::Handle handle, const Effekseer::Color& color)
	{
		if (m_Manager != nullptr)
			m_Manager->SetAllColor(handle, color);
	}

	void EffekseerManager::SetRotation(Effekseer::Handle handle, const Effekseer::Vector3D& rot)
	{
		if (m_Manager != nullptr)
			m_Manager->SetRotation(handle, rot.X, rot.Y, rot.Z);
	}

	void EffekseerManager::SetScale(Effekseer::Handle handle, const Effekseer::Vector3D& scale)
	{
		if (m_Manager != nullptr)
			m_Manager->SetScale(handle, scale.X, scale.Y, scale.Z);
	}

	void EffekseerManager::SetCamera(const Effekseer::Matrix44& view, const Effekseer::Matrix44& proj)
	{
		if (m_Renderer == nullptr) return;
		m_Renderer->SetCameraMatrix(view);
		m_Renderer->SetProjectionMatrix(proj);
	}

}
