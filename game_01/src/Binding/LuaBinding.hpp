#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <SDL2/SDL.h>

#include <string>
#include <tuple>

#include "../AnimationManager/AnimationManager.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/DirectionComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

/**
 * @file LuaBinding.hpp
 * @brief Exposes engine functionality to Lua scripts.
 */

//* Animations

/**
 * @brief Changes the active animation of an entity.
 *
 * @param entity Entity whose animation will be changed.
 * @param animationId Id of the target animation.
 */
void ChangeAnimation(Entity entity, const std::string& animationId) {
  auto& animation = entity.GetComponent<AnimationComponent>();
  auto& sprite = entity.GetComponent<SpriteComponent>();

  animation.animationId = animationId;

  AnimationData animationData;
  animationData = Game::GetInstance().animationManager->GetAnimation(
    animationId);
  
  sprite.textureId = animationData.textureId;
  sprite.width = animationData.width;
  sprite.height = animationData.height;
  sprite.srcRect.x = 0;
  sprite.srcRect.y = 0;

  animation.currentFrame = 1;
  animation.startTime = SDL_GetTicks();
}

//* Audio

/**
 * @brief Plays a sound effect.
 *
 * @param soundId Id of the sound to play.
 */
void PlaySound(const std::string soundId) {
  Game::GetInstance().audioManager->PlaySound(soundId);
}

//* Collisions

/**
 * @brief Checks if an entity collides with another entity on its left side.
 *
 * @param e Primary entity.
 * @param other Entity being checked against.
 * @return True if a left-side collision is detected.
 */
bool LeftCollision(Entity e, Entity other) {
  const auto& eCollider = e.GetComponent<BoxColliderComponent>();
  const auto& eTransform = e.GetComponent<TransformComponent>();

  const auto& oCollider = other.GetComponent<BoxColliderComponent>();
  const auto& oTransform = other.GetComponent<TransformComponent>();

  float eX = eTransform.previousPosition.x + eCollider.offset.x;
  float eY = eTransform.previousPosition.y + eCollider.offset.y;
  float eH = static_cast<float>(eCollider.height);

  float oX = oTransform.previousPosition.x + oCollider.offset.x;
  float oY = oTransform.previousPosition.y + oCollider.offset.y;
  float oH = static_cast<float>(oCollider.height);

  // El lado izquierdo de e choca contra other
  return (
    oY < eY + eH &&
    oY + oH > eY &&
    oX < eX
  );
}

/**
 * @brief Checks if an entity collides with another entity on its right side.
 *
 * @param e Primary entity.
 * @param other Entity being checked against.
 * @return True if a right-side collision is detected.
 */
bool RightCollision(Entity e, Entity other) {
  const auto& eCollider = e.GetComponent<BoxColliderComponent>();
  const auto& eTransform = e.GetComponent<TransformComponent>();

  const auto& oCollider = other.GetComponent<BoxColliderComponent>();
  const auto& oTransform = other.GetComponent<TransformComponent>();

  float eX = eTransform.previousPosition.x + eCollider.offset.x;
  float eY = eTransform.previousPosition.y + eCollider.offset.y;
  float eH = static_cast<float>(eCollider.height);

  float oX = oTransform.previousPosition.x + oCollider.offset.x;
  float oY = oTransform.previousPosition.y + oCollider.offset.y;
  float oH = static_cast<float>(oCollider.height);

  // El lado derecho de e choca contra other
  return (
    oY < eY + eH &&
    oY + oH > eY &&
    oX > eX
  );
}

//* Controls

/**
 * @brief Checks whether a controller action is active.
 *
 * @param action Name of the action to check.
 * @return True if the action is currently active.
 */
bool IsActionActivated(const std::string& action) {
  return Game::GetInstance().controllerManager->isActionActivated(action);
}

//* DirectionComponent

/**
 * @brief Sets the direction vector of an entity.
 *
 * @param entity Target entity.
 * @param x Horizontal direction value.
 * @param y Vertical direction value.
 */
void SetDirection(Entity entity, float x, float y) {
  auto& dir = entity.GetComponent<DirectionComponent>();
  dir.direction = {x, y};
}

//* LayerComponent

/**
 * @brief Retrieves the layer of an entity.
 *
 * @param entity Target entity.
 * @return Layer value.
 */
int GetLayer(Entity entity) {
  return entity.GetComponent<LayerComponent>().z;
}

/**
 * @brief Removes a layer from the game and handles win condition.
 *
 * @param z Layer id to remove.
 */
void RemoveLayer(int z) {
  Game::GetInstance().registry->GetSystem<LayerSystem>().RemoveLayer(z);

  Game::GetInstance().buttonCount--;
  if (Game::GetInstance().buttonCount <= 0) {
    // win
    Game::GetInstance().sceneManager->SetNextScene("win");
    Game::GetInstance().sceneManager->StopScene();
  }
}

//* RigidBodyComponent

/**
 * @brief Retrieves the velocity of an entity.
 *
 * @param entity Target entity.
 * @return Velocity vector as an integer tuple.
 */
std::tuple<int, int> GetVelocity(Entity entity) {
  const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

  return {
    static_cast<int>(rigidbody.velocity.x),
    static_cast<int>(rigidbody.velocity.y),
  };
}

/**
 * @brief Sets the velocity of an entity.
 *
 * @param entity Target entity.
 * @param x Horizontal velocity.
 * @param y Vertical velocity.
 */
void SetVelocity(Entity entity, float x, float y) {
  auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
  rigidBody.velocity.x = x;
  rigidBody.velocity.y = y;
}

/**
 * @brief Applies force to an entity.
 *
 * @param entity Target entity.
 * @param x Horizontal force.
 * @param y Vertical force.
 */
void AddForce(Entity entity, float x, float y) {
  auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
  rigidBody.sumForces += glm::vec2(x, y);
} 

//* Scenes

/**
 * @brief Transitions to another scene.
 *
 * @param sceneName Name of the target scene.
 */
void GoToScene(const std::string& sceneName) {
  Game::GetInstance().sceneManager->SetNextScene(sceneName);
  Game::GetInstance().sceneManager->StopScene();
}

//* Sprites

/**
 * @brief Flips an entity sprite horizontally.
 *
 * @param entity Target entity.
 * @param flip True to flip the sprite.
 */
void FlipSprite(Entity entity, bool flip) {
  auto& sprite = entity.GetComponent<SpriteComponent>();
  sprite.flip = flip;
}

//* TagComponent

/**
 * @brief Retrieves the tag of an entity.
 *
 * @param entity Target entity.
 * @return Entity tag string.
 */
std::string GetTag(Entity entity) {
  return entity.GetComponent<TagComponent>().tag;
}

//* TransformComponent

/**
 * @brief Retrieves the position of an entity.
 *
 * @param entity Target entity.
 * @return Position as an integer tuple.
 */
std::tuple<int, int> GetPosition(Entity entity) {
  const auto& transform = entity.GetComponent<TransformComponent>();

  return {
    static_cast<int>(transform.position.x),
    static_cast<int>(transform.position.y),
  };
}

/**
 * @brief Sets the position of an entity.
 *
 * @param entity Target entity.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
void SetPosition(Entity entity, int x, int y) {
  auto& transform = entity.GetComponent<TransformComponent>();

  transform.position.x = x;
  transform.position.y = y;
}

/**
 * @brief Retrieves the rendered size of an entity.
 *
 * @param entity Target entity.
 * @return Width and height as an integer tuple.
 */
std::tuple<int, int> GetSize(Entity entity) {
  const auto& sprite = entity.GetComponent<SpriteComponent>();
  const auto& transform = entity.GetComponent<TransformComponent>();

  int width = sprite.width * transform.scale.x;
  int height = sprite.height * transform.scale.y;

  return {width, height};
}

//* UI

/**
 * @brief Toggles the paused state of the game.
 */
void TogglePause() {
  Game::GetInstance().isPaused = !Game::GetInstance().isPaused;
}

#endif  // LUABINDING_HPP