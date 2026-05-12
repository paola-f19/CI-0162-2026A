#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <map>
#include <string>

/**
 * @brief Manages game audio resources and playback.
 */
class AudioManager {
  private:
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, Mix_Music*> music;

  public:
    /**
     * @brief Constructor.
     */
    AudioManager();
    /**
     * @brief Destructor.
     */
    ~AudioManager();

    /**
     * @brief Removes and frees all loaded audio assets.
     */
    void ClearAudio();

    /**
     * @brief Loads and stores a sound effect.
     *
     * @param id Id used to access the sound effect.
     * @param path File path of the audio file.
     */
    void LoadSound(const std::string& id, const std::string& path);

    /**
     * @brief Loads and stores a music track.
     *
     * @param id Id used to access the music track.
     * @param path File path of the audio file.
     */
    void LoadMusic(const std::string& id, const std::string& path);

    /**
     * @brief Plays a sound effect.
     *
     * @param id Id of the sound effect to play.
     */
    void PlaySound(const std::string& id);

    /**
     * @brief Plays a music track.
     *
     * @param id Id of the music track to play.
     */
    void PlayMusic(const std::string& id);

    /**
     * @brief Stops the currently playing music track.
     */
    void StopMusic();
};

#endif  // AUDIOMANAGER_HPP