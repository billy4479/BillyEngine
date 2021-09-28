#include "EntityManager.hpp"

#include "../Application.hpp"
#include "../Components/Components.hpp"
#include "../Rendering/Renderer.hpp"

namespace BillyEngine {
EntityManager::EntityManager(Application *application)
    : m_Application(application) {}

EntityManager::~EntityManager() { m_Registry.clear(); }

void EntityManager::Update(f32 delta) {
    BE_PROFILE_FUNCTION();

    {
        BE_PROFILE_SCOPE("Scripts");
        m_Registry.view<Components::Script>().each(
            [&](auto entity, Components::Script &script) {
                (void)entity;
                // auto e = Entity(entity, this);
                if (!script.WasOnCreateCalled) script.OnCreate();

                script.OnUpdate(delta);
            });
    }
    {
        BE_PROFILE_SCOPE("Text");
        m_Registry.group<Components::Text, Components::Transform>().each(
            [&](auto entity, Components::Text &label,
                Components::Transform &t) {
                (void)entity;
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
            [&](auto entity, Components::Sprite &sprite,
                Components::Transform &t) {
                (void)entity;
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
    if (name.empty()) {
        std::stringstream ss;
        ss << "Entity [" << (u32)e << "]";
        ss >> n;
    } else {
        n = name;
    }

    e.AddComponent<Components::ID>();
    e.AddComponent<Components::Tag>(name);
    e.AddComponent<Components::Transform>();

    return e;
}

void EntityManager::DestroyEntity(Entity entity) { m_Registry.destroy(entity); }

}  // namespace BillyEngine
