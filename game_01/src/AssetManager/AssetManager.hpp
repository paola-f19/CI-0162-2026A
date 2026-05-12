#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>

/**
 * @brief Manages game assets such as textures and fonts.
 */
class AssetManager {
  private:
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;

  public:
    /**
     * @brief Constructor.
     */
    AssetManager();
    /**
     * @brief Destructor.
     */
    ~AssetManager();

    /**
     * @brief Removes and frees all loaded assets.
     */
    void ClearAssets();

    /**
     * @brief Loads and stores a texture.
     *
     * @param renderer SDL renderer used to create the texture.
     * @param textureId Id used to access the texture.
     * @param filePath File path of the texture image.
     */
    void AddTexture(SDL_Renderer* renderer, const std::string& textureId
      , const std::string& filePath);

    /**
     * @brief Texture getter.
     *
     * @param textureId Id of the requested texture.
     * @return Pointer to the requested texture.
     */
    SDL_Texture* GetTexture(const std::string& textureId);

    /**
     * @brief Loads and stores a font.
     *
     * @param fontId Id used to access the font.
     * @param filePath File path of the font file.
     * @param fontSize Font size used when loading the font.
     */
    void AddFont(const std::string& fontId, const std::string& filePath
      , int fontSize);

    /**
     * @brief Font getter.
     *
     * @param fontId Id of the requested font.
     * @return Pointer to the requested font.
     */
    TTF_Font* GetFont(const std::string& fontId);
};

#endif  // ASSETMANAGER_HPP