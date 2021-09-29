#include "UUID.hpp"

#include "Common.hpp"
#include "spdlog/fmt/bundled/core.h"

namespace BillyEngine {

static std::random_device device;
static std::mt19937_64 engine(device());
static std::uniform_int_distribution<u64> distribution;

UUID::UUID() : m_UUID(distribution(engine)) {}

UUID::UUID(u64 id) : m_UUID(id) {}

UUID::operator u64() const { return m_UUID; }

std::string UUID::ToString() const { return fmt::format("{:08x}", m_UUID); }
}  // namespace BillyEngine