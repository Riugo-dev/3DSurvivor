//	effect_spawner.cpp
//	
//	2025.11.17			大山凌太朗

#include "main.h"
#include "effect_spawner.h"

using namespace math;

namespace app {
    EffectSpawner::Instance EffectSpawner::Spawn(const std::string effectFileName, const /*math::*/Vector3& pos, const /*math::*/Vector3& size, const math::Quaternion& rot)
    {
        Instance inst;

        auto manager = graphics::EffekseerManager::GetInstance();
        if (!manager) return inst;

        // エフェクト読み込み
        auto effect = manager->LoadEffect(effectFileName);
        if (effect == nullptr) return inst;

        Effekseer::Vector3D efpos = { pos.x,pos.y,pos.z };

        // 再生
        inst.handle = manager->PlayEffect(
            effectFileName,
            efpos
        );

        auto efMgr = manager->GetManager();
        if (efMgr == nullptr) return inst;

        // ------ パラメータ設定 ------

        efMgr->SetLocation(inst.handle,pos.x, pos.y, pos.z);


        Vector3 eulerRot = rot.ToEulerRad();
        efMgr->SetRotation(inst.handle,
            eulerRot.x, eulerRot.y, eulerRot.z
        );

        efMgr->SetScale(inst.handle,
            size.x, size.y, size.z
        );
        return inst;
    }
    EffectSpawner::Instance EffectSpawner::Spawn(const std::string effectFileName, const SpawnParam& param)
    {
        Instance inst;

        auto manager = graphics::EffekseerManager::GetInstance();
        if (!manager) return inst;

        // エフェクト読み込み
        auto effect = manager->LoadEffect(effectFileName);
        if (effect == nullptr) return inst;

        // 再生
        inst.handle = manager->PlayEffect(
            effectFileName,
            { param.position.x, param.position.y, param.position.z }
        );

        inst.loop = param.loop;

        auto efMgr = manager->GetManager();
        if (efMgr == nullptr) return inst;

        // ------ パラメータ設定 ------
        efMgr->SetSpeed(inst.handle, param.playSpeed);

        efMgr->SetLocation(inst.handle, param.position.x, param.position.y, param.position.z);

        Vector3 eulerRot = param.rotation.ToEulerRad();
        efMgr->SetRotation(inst.handle,
            eulerRot.x, eulerRot.y, eulerRot.z
        );

        efMgr->SetScale(inst.handle,
            param.size.x, param.size.y, param.size.z
        );

        Effekseer::Color color(
            static_cast<uint8_t>(param.color.r * 255),
            static_cast<uint8_t>(param.color.g * 255),
            static_cast<uint8_t>(param.color.b * 255),
            static_cast<uint8_t>(param.color.a * 255)
        );
        efMgr->SetAllColor(inst.handle, color);

        return inst;
    }

    void EffectSpawner::Stop(const Instance& inst)
    {
        if (inst.handle < 0) return;

        auto manager = graphics::EffekseerManager::GetInstance();
        if (!manager) return;

        manager->StopEffect(inst.handle);
    }

    bool EffectSpawner::Exists(Effekseer::Handle handle)
    {
        if (handle < 0) return false;

        auto manager = graphics::EffekseerManager::GetInstance();
        if (!manager) return false;

        auto efMgr = manager->GetManager();
        if (efMgr == nullptr) return false;

        return efMgr->Exists(handle);
    }
}