#pragma once

#include "../Application.hpp"
#include "../Components/Components.hpp"
#include "../Core/Common.hpp"
#include "../Entity/EntityManager.hpp"
#include "../Entity/ScriptableEntity.hpp"
#include "../Rendering/DrawableTexture.hpp"

#define SCRIPTABLE_ENTITY(className)                                       \
    className(BillyEngine::Entity e) : BillyEngine::ScriptableEntity(e) {} \
    BE_NON_COPY_CONSTRUCTIBLE(className)
