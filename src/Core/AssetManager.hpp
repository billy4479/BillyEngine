#pragma once

#include "Common.hpp"

class Application;

class AssetManager {
   public:
    AssetManager(Application *a) : m_App(a) {}
    AssetManager(const AssetManager &) = delete;
    ~AssetManager();

    void LoadFont(const std::filesystem::path &, const std::string &, u32);
    TTF_Font *GetFont(const std::string &);

    void LoadImage(const std::filesystem::path &, const std::string);

    void ReleaseSDLModules();

   private:
    Application *m_App;
    const std::filesystem::path m_AssetsFolder{"assets"};
    std::map<const std::string, TTF_Font *> m_Fonts;
    std::map<const std::string, SDL_Texture *> m_Textures;
};
