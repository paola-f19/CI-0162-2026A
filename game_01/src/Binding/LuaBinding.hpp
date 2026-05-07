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

//* Animations

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
void PlaySound(const std::string soundId) {
  Game::GetInstance().audioManager->PlaySound(soundId);
}

//* Collisions

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

//* Controles

bool IsActionActivated(const std::string& action) {
  return Game::GetInstance().controllerManager->isActionActivated(action);
}

//* DirectionComponent
void SetDirection(Entity entity, float x, float y) {
  auto& dir = entity.GetComponent<DirectionComponent>();
  dir.direction = {x, y};
}

//* LayerComponent

int GetLayer(Entity entity) {
  return entity.GetComponent<LayerComponent>().z;
}


void RemoveLayer(int z) {
  // std::cout << "[LUABINDING] entered RemoveLayer with z = " << z << std::endl;
  Game::GetInstance().registry->GetSystem<LayerSystem>().RemoveLayer(z);

  Game::GetInstance().buttonCount--;
  if (Game::GetInstance().buttonCount <= 0) {
    // win
    Game::GetInstance().sceneManager->SetNextScene("win");
    Game::GetInstance().sceneManager->StopScene();
  }
}

//* RigidBodyComponent

std::tuple<int, int> GetVelocity(Entity entity) {
  const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

  return {
    static_cast<int>(rigidbody.velocity.x),
    static_cast<int>(rigidbody.velocity.y),
  };
}

void SetVelocity(Entity entity, float x, float y) {
  auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
  rigidBody.velocity.x = x;
  rigidBody.velocity.y = y;
}

void AddForce(Entity entity, float x, float y) {
  auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
  rigidBody.sumForces += glm::vec2(x, y);
} 

//* Scenes

void GoToScene(const std::string& sceneName) {
  Game::GetInstance().sceneManager->SetNextScene(sceneName);
  Game::GetInstance().sceneManager->StopScene();
}

//* Sprites
void FlipSprite(Entity entity, bool flip) {
  auto& sprite = entity.GetComponent<SpriteComponent>();
  sprite.flip = flip;
}

//* TagComponent

std::string GetTag(Entity entity) {
  return entity.GetComponent<TagComponent>().tag;
}

//* TransformComponent

std::tuple<int, int> GetPosition(Entity entity) {
  const auto& transform = entity.GetComponent<TransformComponent>();

  return {
    static_cast<int>(transform.position.x),
    static_cast<int>(transform.position.y),
  };
}

void SetPosition(Entity entity, int x, int y) {
  auto& transform = entity.GetComponent<TransformComponent>();

  transform.position.x = x;
  transform.position.y = y;
}

std::tuple<int, int> GetSize(Entity entity) {
  const auto& sprite = entity.GetComponent<SpriteComponent>();
  const auto& transform = entity.GetComponent<TransformComponent>();

  int width = sprite.width * transform.scale.x;
  int height = sprite.height * transform.scale.y;

  return {width, height};
}

//* UI
void TogglePause() {
  Game::GetInstance().isPaused = !Game::GetInstance().isPaused;
}

#endif  // LUABINDING_HPP