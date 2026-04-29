#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <map>
#include <string>

class AudioManager {
  private:
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, Mix_Music*> music;

  public:
    AudioManager();
    ~AudioManager();

    void ClearAudio();

    void LoadSound(const std::string& id, const std::string& path);

    void LoadMusic(const std::string& id, const std::string& path);

    void PlaySound(const std::string& id);

    void PlayMusic(const std::string& id);

    void StopMusic();
};

#endif  // AUDIOMANAGER_HPP