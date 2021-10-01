#include "EntityManager.hpp"

#include "../Application.hpp"
#include "../Components/Components.hpp"
#include "../Rendering/Renderer.hpp"
#include "Entity.hpp"

namespace BillyEngine {
EntityManager::EntityManager(Application *application)
    : m_Application(application) {}

EntityManager::~EntityManager() { m_Registry.clear(); }

void EntityManager::Update(f32 delta) {
    BE_PROFILE_FUNCTION();

    {
        BE_PROFILE_SCOPE("Scripts");
        m_Registry.view<Components::ScriptManager>().each(
            [&](Components::ScriptManager &sm) {
                sm.RegisterAllComponents();

                sm.CreateAll();
                HandleDestruction();

                sm.UpdateAll(delta);
                HandleDestruction();
            });
    }
    {
        BE_PROFILE_SCOPE("Text");
        m_Registry.group<Components::Text, Components::Transform>().each(
            [&](Components::Text &label, Components::Transform &t) {
                if (label.m_Texture == nullptr) {
                    BE_ASSERT(label.m_Font != nullptr);
                    label.m_Texture =
                        m_Application->m_Renderer->RenderTextToTexture(
                            label.m_Content, label.m_Font, label.m_Color);
                }
                m_Application->m_Renderer->DrawTexture(label.m_Texture, t);
            });
    }
    {
        BE_PROFILE_SCOPE("Sprites");
        m_Registry.view<Components::Sprite, Components::Transform>().each(
            [&](Components::Sprite &sprite, Components::Transform &t) {
#ifdef DEBUG
                if (sprite.GetTexture() != nullptr)
#endif
                    m_Application->m_Renderer->DrawTexture(sprite.GetTexture(),
                                                           t, sprite.Tint);
#ifdef DEBUG
                else
                    BE_CORE_WARN("Not drawing since the texture is null");
#endif
            });
    }
}

Entity EntityManager::CreateEntity(const std::string &name) {
    Entity e = {m_Registry.create(), this};

    std::string n;
    if (name.empty())
        n = fmt::format("Entity [{}]", (u32)e);
    else
        n = name;

    e.AddComponent<Components::ID>();
    e.AddComponent<Components::Tag>(n);
    e.AddComponent<Components::Transform>();

    return e;
}

void EntityManager::DestroyEntity(Entity entity) {
    m_DestructionQueue.push_back(entity);
    // m_Registry.destroy(entity);
}

Entity EntityManager::FindEntityByID(UUID uuid) {
    auto view = m_Registry.view<Components::ID>();

    for (auto it = view.begin(); it != view.end(); it++) {
        if (static_cast<UUID>(m_Registry.get<Components::ID>(*it)) == uuid)
            return Entity(*it, this);
    }
    return Entity(entt::null, this);
}

Entity EntityManager::FindEntityByTag(std::string_view tag) {
    auto view = m_Registry.view<Components::Tag>();

    for (auto it = view.begin(); it != view.end(); it++) {
        if (m_Registry.get<Components::Tag>(*it).Name == tag)
            return Entity(*it, this);
    }
    return Entity(entt::null, this);
}

template <typename Component>
void EntityManager::DuplicateComponentIfPresent(Entity dst, Entity src) {
    if constexpr (std::is_same_v<Component, Components::ScriptManager>) {
        if (src.HasComponent<Components::ScriptManager>()) {
            auto &srcSm = src.GetComponent<Components::ScriptManager>();
            dst.AddComponent<Components::ScriptManager>(dst);
            for (auto &ac : srcSm.m_Components) {
                ac.AddToEntity(dst);
            }
        }
    } else {
        if (src.HasComponent<Component>())
            dst.AddComponent<Component>(src.GetComponent<Component>());
    }
}

Entity EntityManager::Duplicate(Entity src) {
    Entity dst = {m_Registry.create(), this};

    dst.AddComponent<Components::ID>();

    DuplicateComponentIfPresent<Components::Transform>(dst, src);
    DuplicateComponentIfPresent<Components::Sprite>(dst, src);
    DuplicateComponentIfPresent<Components::Tag>(dst, src);
    DuplicateComponentIfPresent<Components::Text>(dst, src);
    DuplicateComponentIfPresent<Components::ScriptManager>(dst, src);

    return dst;
}

void EntityManager::HandleDestruction() noexcept {
    if (!m_DestructionQueue.empty()) {
        for (auto e : m_DestructionQueue) m_Registry.destroy(e);
        m_DestructionQueue.clear();
    }
}

}  // namespace BillyEngine
