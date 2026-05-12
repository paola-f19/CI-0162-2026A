#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "SceneLoader.hpp"

/**
 * @brief Manages game scenes and scene transitions.
 */
class SceneManager {
  private:
    std::map<std::string, std::string> scenes;
    std::string nextScene;
    bool isSceneRunning = false;
    std::unique_ptr<SceneLoader> sceneLoader;

  public:
    /**
     * @brief Constructor.
     */
    SceneManager();
    /**
     * @brief Destructor.
     */
    ~SceneManager();

    /**
     * @brief Loads scene definitions from a Lua script.
     *
     * @param path File path of the Lua scene script.
     * @param lua Lua state used to execute the script.
     */
    void LoadSceneFromScript(const std::string& path, sol::state& lua);

    /**
     * @brief Loads the currently selected scene.
     */
    void LoadScene();

    /**
     * @brief Retrieves the id of the next scene.
     *
     * @return Name of the next scene.
     */
    std::string GetNextScene() const;

    /**
     * @brief Sets the next scene to load.
     *
     * @param nextScene Name of the target scene.
     */
    void SetNextScene(const std::string& nextScene);

    /**
     * @brief Checks whether a scene is currently running.
     *
     * @return True if a scene is active.
     */
    bool IsSceneRunning() const;

    /**
     * @brief Starts scene execution.
     */
    void StartScene();

    /**
     * @brief Stops the current scene.
     */
    void StopScene();
};

#endif  // SCENEMANAGER_HPP