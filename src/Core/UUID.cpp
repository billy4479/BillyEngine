#include "Core/UUID.hpp"

#include <spdlog/fmt/fmt.h>

#include <random>

namespace BillyEngine {

static std::random_device device;
static std::mt19937_64 engine(device());
static std::uniform_int_distribution<u64> distribution;

UUID::UUID() : m_UUID(distribution(engine)) {}

UUID::UUID(u64 uuid) : m_UUID(uuid) {}

UUID::operator u64() const { return m_UUID; }

std::string UUID::ToString() const { return fmt::format("{:08x}", m_UUID); }

}  // namespace BillyEngine