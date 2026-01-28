//	effect_spawner.h
//	
//	2025.11.17			大山凌太朗

#ifndef EFFECT_SPAWNER_H
#define EFFECT_SPAWNER_H

#include "manager_effekseer.h"
#include "utils_math.h"
#include "utils_quaternion.h"
#include "utils_color.h"
#include "vector3.h"
#include <string>
#include <vector>

namespace app{
    class EffectSpawner {
    public:
        struct Instance {
            Effekseer::Handle handle = -1;
            bool loop = false;
        };

        struct SpawnParam {
            bool loop = false;                 // ループ再生
            float playSpeed = 1.0f;            // 再生速度

            Vector3 position = { 0.0f,0.0f,0.0f };
            //math::Vector3 position = { 0.0f,0.0f,0.0f };
            math::Quaternion rotation = { 0.0f,0.0f,0.0f,1.0f };
            Vector3 size = { 1.0f,1.0f,1.0f };
            //math::Vector3 size = { 1.0f,1.0f,1.0f };
            math::Color4 color = { 1.0f,1.0f,1.0f,1.0f };
        };

    public:
        //生成

        //Transform生成
        static Instance Spawn(const std::string effectFileName, 
                              const /*math::*/Vector3& pos, 
                              const /*math::*/Vector3& size = /*math::*/Vector3(1.0f, 1.0f, 1.0f), 
                              const math::Quaternion& rot = math::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
       
        //詳細生成
        static Instance Spawn(const std::string effectFileName,const SpawnParam& param);


        static void Stop(const Instance& inst);
        static bool Exists(Effekseer::Handle handle);
    };
}

#endif // EFFECT_SPAWNER_H
