#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>
#include <tuple>

/**
 * @brief Manages keyboard and mouse input mappings.
 */
class ControllerManager {
  private:
    std::map<std::string, int> actionKeyName;
    std::map<int, bool> keyDown;

    std::map<std::string, int> mouseButtonName;
    std::map<int, bool> mouseButtonDown;

    int mousePosX;
    int mousePosY;

  public:
    /**
     * @brief Constructor.
     */
    ControllerManager();
    /**
     * @brief Destructor.
     */
    ~ControllerManager();

    /**
     * @brief Clears stored input bindings and states.
     */
    void Clear();

    //* Keyboard

    /**
     * @brief Binds an action name to a keyboard key.
     *
     * @param action Name of the action.
     * @param keyCode SDL key code associated with the action.
     */
    void AddActionKey(const std::string& action, int keyCode);

    /**
     * @brief Registers a key press event.
     *
     * @param keyCode SDL key code that was pressed.
     */
    void KeyDown(int keyCode);

    /**
     * @brief Registers a key release event.
     *
     * @param keyCode SDL key code that was released.
     */
    void KeyUp(int keyCode);

    /**
     * @brief Checks whether an action is currently active.
     *
     * @param action Name of the action to check.
     * @return True if the action is active.
     */
    bool isActionActivated(const std::string& action);

    //* Mouse

    /**
     * @brief Binds a name to a mouse button.
     *
     * @param name Name of the mouse button action.
     * @param buttonCode SDL mouse button code.
     */
    void AddMouseButton(const std::string& name, int buttonCode);

    /**
     * @brief Registers a mouse button press event.
     *
     * @param buttonCode SDL mouse button code that was pressed.
     */
    void MouseButtonDown(int buttonCode);

    /**
     * @brief Registers a mouse button release event.
     *
     * @param buttonCode SDL mouse button code that was released.
     */
    void MouseButtonUp(int buttonCode);

    /**
     * @brief Checks whether a mouse button is currently pressed.
     *
     * @param name Name of the mouse button action.
     * @return True if the button is pressed.
     */
    bool IsMouseButtonDown(const std::string& name);

    /**
     * @brief Updates the current mouse cursor position.
     *
     * @param x Horizontal mouse position.
     * @param y Vertical mouse position.
     */
    void SetMousePosition(int x, int y);

    /**
     * @brief Retrieves the current mouse cursor position.
     *
     * @return Mouse position as an integer tuple.
     */
    std::tuple<int, int> GetMousePosition();
};

#endif  // CONTROLLERMANAGER_HPP