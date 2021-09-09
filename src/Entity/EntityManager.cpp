#include "EntityManager.hpp"

#include "../Application.hpp"
#include "../Components/Components.hpp"

namespace BillyEngine {
EntityManager::EntityManager(Application *application)
    : m_Application(application) {}

EntityManager::~EntityManager() { m_Registry.clear(); }

void EntityManager::Update(f32 delta) {
    m_Registry.view<Components::Script>().each([&](auto entity, auto &script) {
        (void)entity;
        // auto e = Entity(entity, this);
        if (script.Instance == nullptr) script.Instantiate();
        if (!script.WasOnCreateCalled) script.OnCreate(script.Instance);

        script.OnUpdate(script.Instance, delta);
    });

    m_Registry.view<Components::Text, Components::Transform>().each(
        [&](auto entity, auto &label, auto &t) {
            (void)entity;
            if (label.m_Texture == nullptr) {
                BE_ASSERT(label.m_Font != nullptr);
                label.m_Texture =
                    m_Application->GetRenderer()->RenderTextToTexture(
                        label.m_Content, label.m_Font, label.fgColor);
            }
            m_Application->GetRenderer()->DrawTexture(
                label.m_Texture, t.Position, t.Scale, t.Rotation, t.Anchor,
                t.RotationCenter);
        });

    m_Registry.view<Components::Sprite, Components::Transform>().each(
        [&](auto entity, auto &sprite, auto &t) {
            (void)entity;
#ifdef DEBUG
            if (sprite.GetTexture() != nullptr)
#endif
                m_Application->GetRenderer()->DrawTexture(
                    sprite.GetTexture(), t.Position, t.Scale, t.Rotation,
                    t.Anchor, t.RotationCenter);
#ifdef DEBUG
            else
                dbg_print("Not drawing since the texture is null\n");
#endif
        });
}

Entity EntityManager::CreateEntity(const std::string &name) {
    Entity e = {m_Registry.create(), this};

    std::string n;
    if (name.empty()) {
        std::stringstream ss;
        ss << "Entity [" << (u32)e << "]";
        ss >> n;
    } else {
        n = name;
    }

    e.AddComponent<Components::Tag>(name);
    e.AddComponent<Components::Transform>();

    return e;
}

void EntityManager::DestroyEntity(Entity entity) { m_Registry.destroy(entity); }

}  // namespace BillyEngine
