#ifndef GAME_APP
#define GAME_APP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <sol/sol.hpp>

#include "../AnimationManager/AnimationManager.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../AudioManager/AudioManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"

const int FPS = 30;
const int MILLISECS_PER_FRAME = 1000 / FPS;

/**
 * @brief Main game engine controller.
 */
class Game {
  private:
    SDL_Window* window = nullptr;

    SDL_Rect camera = { 0, 0, 0, 0 };

    int millisecsPreviousFrame = 0;

    bool isRunning = false;
    bool isDebugMode = false;

  public:
    SDL_Renderer* renderer = nullptr;

    std::unique_ptr<AnimationManager> animationManager;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<AudioManager> audioManager;
    std::unique_ptr<ControllerManager> controllerManager;
    std::unique_ptr<EventManager> eventManager;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<SceneManager> sceneManager;
    sol::state lua;

    bool isPaused = false;
    bool isGameOver = false;
    int buttonCount = 2;

    int windowWidth = 0;
    int windowHeight = 0;

    int mapWidth = 0;
    int mapHeight = 0;

  private:
    /**
     * @brief Initializes game systems and resources.
     */
    void SetUp();

    /**
     * @brief Executes the current scene.
     */
    void RunScene();

    /**
     * @brief Processes SDL input events.
     */
    void ProcessInput();

    /**
     * @brief Updates game logic.
     */
    void Update();

    /**
     * @brief Renders the current game frame.
     */
    void Render();

    /**
     * @brief Constructor.
     */
    Game();
    /**
     * @brief Destructor.
     */
    ~Game();

  public:
    /**
     * @brief Retrieves the singleton game instance.
     *
     * @return Reference to the game instance.
     */
    static Game& GetInstance();

    /**
     * @brief Initializes the game engine.
     */
    void Init();

    /**
     * @brief Starts the main game loop.
     */
    void Run();

    /**
     * @brief Frees game resources and shuts down the engine.
     */
    void Destroy();
};

#endif  // GAME_APP