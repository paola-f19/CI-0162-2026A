#include "AssetManager.hpp"

#include <SDL2/SDL_image.h>

#include <iostream>

AssetManager::AssetManager() {
  std::cout << "[ASSETMANAGER] Se ejecuta constructor" << std::endl;
}

AssetManager::~AssetManager() {
  std::cout << "[ASSETMANAGER] Se ejecuta destructor" << std::endl;
}

void AssetManager::ClearAssets() {
  for (auto texture : textures) {
    SDL_DestroyTexture(texture.second);
  }
  textures.clear();

  for (auto font : fonts) {
    TTF_CloseFont(font.second);
  }
  fonts.clear(); 
}

void AssetManager::AddTexture(SDL_Renderer* renderer
  , const std::string& textureId, const std::string& filePath) {
  SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
    std::cout << "[ERROR] Failed to load surface: " << filePath << std::endl;
    return;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    std::cout << "[ERROR] Failed to create texture: " << filePath << std::endl;
    return;
  }
  SDL_FreeSurface(surface);

  textures.emplace(textureId, texture);

  // std::cout << "[INFO] Loaded texture: " << textureId << std::endl;
}

SDL_Texture* AssetManager::GetTexture(const std::string& textureId) {
  return textures[textureId];
}

void AssetManager::AddFont(const std::string& fontId, const std::string& filePath
  , int fontSize) {
  TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
  if (font == NULL) {
    std::string error = TTF_GetError();
    std::cerr << "[ASSETMANAGER] " << error << std::endl;
    return;
  }
  fonts.emplace(fontId, font);
}

TTF_Font* AssetManager::GetFont(const std::string& fontId) {
  return fonts[fontId];
}