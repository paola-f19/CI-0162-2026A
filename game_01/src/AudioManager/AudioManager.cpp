#include "AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager() {
  std::cout << "[AUDIOMANAGER] Se ejecuta constructor" << std::endl;
}

AudioManager::~AudioManager() {
  std::cout << "[AUDIOMANAGER] Se ejecuta destructor" << std::endl;
}

void AudioManager::ClearAudio() {
  for (auto sound : sounds) {
    Mix_FreeChunk(sound.second);
  }
  sounds.clear();

  for (auto song : music) {
    Mix_FreeMusic(song.second);
  }
  music.clear();
}

void AudioManager::LoadSound(const std::string& id, const std::string& path) {
  Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
  if (!chunk) {
    std::string error = Mix_GetError();
    std::cerr << "[AUDIOMANAGER] " << error << std::endl;
    return;
  }
  sounds.emplace(id, chunk);
}

void AudioManager::LoadMusic(const std::string& id, const std::string& path) {
  Mix_Music* mus = Mix_LoadMUS(path.c_str());
  if (!mus) {
    std::string error = Mix_GetError();
    std::cerr << "[AUDIOMANAGER] " << error << std::endl;
    return;
  }
  music.emplace(id, mus);
}

void AudioManager::PlaySound(const std::string& id) {
  Mix_PlayChannel(-1, sounds[id], 0);
}

void AudioManager::PlayMusic(const std::string& id) {
  std::cout << "[AUDIOMANAGER] Playing music: " << id << std::endl;
  Mix_PlayMusic(music[id], -1); // loop
}

void AudioManager::StopMusic() {
  Mix_HaltMusic();
}