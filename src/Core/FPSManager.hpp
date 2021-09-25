#pragma once

#include "Common.hpp"

namespace BillyEngine {
class FPSManager {
   public:
    FPSManager(f32 targetFPS = 60);

    void SetTargetFPS(f32);
    f32 GetTargetFPS() const;
    f32 GetActualFPS() const;

    // In seconds
    f32 GetElapsed() const;

    void StartFrame();
    void EndFrameAndWait();

   private:
    f32 m_TargetFPS;
    u64 m_MinFrameTime;

    u64 m_StartFrame;
    u64 m_Elapsed = 1;
};
}  // namespace BillyEngine