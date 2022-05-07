%module BE
%nspace;

%{
  #include "Application.hpp"
  #include "Assets/AssetManager.hpp"
  #include "Core/Color.hpp"
  #include "Core/UUID.hpp"
  #include "Entity/EntityManager.hpp"
  #include "Events/EventManager.hpp"
  #include "Events/Input.hpp"
  #include "Rendering/Renderer.hpp"
  #include "Rendering/Window.hpp"

  using namespace BillyEngine;
%}

  
%rename(ToU64) BillyEngine::UUID::operator u64;

%include "Application.hpp"
%include "Assets/AssetManager.hpp"
%include "Core/Color.hpp"
%include "Core/UUID.hpp"
%include "Entity/EntityManager.hpp"
%include "Events/EventManager.hpp"
%include "Events/Input.hpp"
%include "Rendering/Renderer.hpp"
%include "Rendering/Window.hpp"
