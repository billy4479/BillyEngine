#include "FPSManager.hpp"

#include "Logger.hpp"

namespace BillyEngine {

FPSManager::FPSManager(f32 targetFPS)
    : m_TargetFPS(targetFPS),
      m_MinFrameTime(static_cast<u64>(1000000.0f / targetFPS)) {}

void FPSManager::SetTargetFPS(f32 fps) {
    m_TargetFPS = fps;
    m_MinFrameTime = static_cast<u64>(1000000.0f / m_TargetFPS);
}

f32 FPSManager::GetTargetFPS() const { return m_TargetFPS; }

f32 FPSManager::GetActualFPS() const {
    return (u32(100.0 / GetElapsed())) / 100.0f;
}

f32 FPSManager::GetElapsed() const { return m_Elapsed / 1000000.0; }

void FPSManager::StartFrame() {
    m_StartFrame = std::chrono::time_point_cast<std::chrono::microseconds>(
                       std::chrono::high_resolution_clock::now())
                       .time_since_epoch()
                       .count();
}

void FPSManager::EndFrameAndWait() {
    u64 end = std::chrono::time_point_cast<std::chrono::microseconds>(
                  std::chrono::high_resolution_clock::now())
                  .time_since_epoch()
                  .count();
    m_Elapsed = end - m_StartFrame;
    if (m_MinFrameTime > m_Elapsed) {
        std::this_thread::sleep_for(
            std::chrono::microseconds(m_MinFrameTime - m_Elapsed));
        // SDL_Delay((m_MinFrameTime - m_Elapsed) / 1000);

        m_Elapsed = m_MinFrameTime;
    }
}

}  // namespace BillyEngine