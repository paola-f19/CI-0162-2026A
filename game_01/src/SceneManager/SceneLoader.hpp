#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "../AnimationManager/AnimationManager.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../AudioManager/AudioManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Stores tileset metadata used for tilemap loading.
 */
struct TilesetData {
  std::string name;
  int firstGid;
  int columns;
};

/**
 * @brief Loads scenes and game resources from external files.
 */
class SceneLoader {
  private:
    /**
     * @brief Loads sprite textures defined in a scene.
     *
     * @param renderer SDL renderer used to create textures.
     * @param sprites Lua table containing sprite definitions.
     * @param assetManager Asset manager used to store textures.
     */
    void LoadSprites(SDL_Renderer* renderer, const sol::table& sprites
      , std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads animation definitions.
     *
     * @param animations Lua table containing animation data.
     * @param animationManager Animation manager used to store animations.
     */
    void LoadAnimations(const sol::table& animations
      , std::unique_ptr<AnimationManager>& animationManager);

    /**
     * @brief Loads sound effects.
     *
     * @param sounds Lua table containing sound definitions.
     * @param audioManager Audio manager used to store sounds.
     */
    void LoadSoundEffects(const sol::table& sounds
      , std::unique_ptr<AudioManager>& audioManager);
    
    /**
     * @brief Loads music tracks.
     *
     * @param music Lua table containing music definitions.
     * @param audioManager Audio manager used to store music.
     */
    void LoadMusic(const sol::table& music
      , std::unique_ptr<AudioManager>& audioManager);

    /**
     * @brief Loads font resources.
     *
     * @param fonts Lua table containing font definitions.
     * @param assetManager Asset manager used to store fonts.
     */
    void LoadFonts(const sol::table& fonts
      , std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads keyboard input bindings.
     *
     * @param keys Lua table containing key bindings.
     * @param controllerManager Controller manager storing bindings.
     */
    void LoadKeys(const sol::table& keys
      , std::unique_ptr<ControllerManager>& controllerManager);

    /**
     * @brief Loads mouse button bindings.
     *
     * @param buttons Lua table containing button bindings.
     * @param controllerManager Controller manager storing bindings.
     */
    void LoadButtons(const sol::table& buttons
      , std::unique_ptr<ControllerManager>& controllerManager);

    /**
     * @brief Loads scene entities and components.
     *
     * @param lua Lua state used for scripting.
     * @param entities Lua table containing entity definitions.
     * @param registry ECS registry storing entities.
     */
    void LoadEntities(sol::state& lua, const sol::table& entities
      , std::unique_ptr<Registry>& registry);

    /**
     * @brief Loads a tilemap.
     *
     * @param map Lua table containing map configuration.
     * @param registry ECS registry storing map entities.
     */
    void LoadMap(const sol::table map, std::unique_ptr<Registry>& registry);

    /**
     * @brief Loads a tilemap layer.
     *
     * @param registry ECS registry storing tile entities.
     * @param layer TMX layer element.
     * @param tWidth Tile width.
     * @param tHeight Tile height.
     * @param mWidth Map width.
     * @param tilesets Tileset metadata list.
     * @param tilesetIndex Active tileset index.
     */
    void LoadLayer(std::unique_ptr<Registry>& registry,
      tinyxml2::XMLElement* layer,
      int tWidth, int tHeight, int mWidth,
      const std::vector<TilesetData>& tilesets, int tilesetIndex);

    /**
     * @brief Loads tilemap collision objects.
     *
     * @param registry ECS registry storing collider entities.
     * @param objectGroup TMX object group element.
     */
    void LoadColliders(std::unique_ptr<Registry>& registry
      , tinyxml2::XMLElement* objectGroup);
  
  public:
    /**
     * @brief Constructor.
     */
    SceneLoader();

    /**
     * @brief Destructor.
     */
    ~SceneLoader();

    /**
     * @brief Loads a complete game scene.
     *
     * @param scenePath File path of the scene script.
     * @param lua Lua state used for scripting.
     * @param animationManager Animation manager instance.
     * @param assetManager Asset manager instance.
     * @param audioManager Audio manager instance.
     * @param controllerManager Controller manager instance.
     * @param registry ECS registry instance.
     * @param renderer SDL renderer used for graphics loading.
     */
    void LoadScene(const std::string& scenePath, sol::state& lua
      , std::unique_ptr<AnimationManager>& animationManager
      , std::unique_ptr<AssetManager>& assetManager
      , std::unique_ptr<AudioManager>& audioManager
      , std::unique_ptr<ControllerManager>& controllerManager
      , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer);
};

#endif  // SCENELOADER_HPP