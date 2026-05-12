#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include <map>
#include <string>

/**
 * @brief Stores configuration data for a sprite animation.
 */
struct AnimationData {
  std::string textureId;
  int row;
  int width;
  int height;
  int numFrames;
  int frameSpeedRate;
  bool isLoop;

  /**
   * @brief Constructor.
   *
   * @param textureId Texture used for the animation.
   * @param row Sprite sheet row containing the animation frames.
   * @param width Width of each frame.
   * @param height Height of each frame.
   * @param numFrames Total number of animation frames.
   * @param frameSpeedRate Animation playback speed.
   * @param isLoop Determines whether the animation repeats.
   */
  AnimationData(
    const std::string& textureId = "",
    int row = 0,
    int width = 0,
    int height = 0,
    int numFrames = 1,
    int frameSpeedRate = 1,
    bool isLoop = true
  ) {
    this->textureId = textureId;
    this->row = row;
    this->width = width;
    this->height = height;
    this->numFrames = numFrames;
    this->frameSpeedRate = frameSpeedRate;
    this->isLoop = isLoop;
  }
};

/**
 * @brief Manages animations used by entities.
 */
class AnimationManager {
  private:
    std::map<std::string, AnimationData> animations;
  public:
    /**
     * @brief Constructor.
     */
    AnimationManager();
    /**
     * @brief Destructor.
     */
    ~AnimationManager();

    /**
     * @brief Registers a new animation.
     *
     * @param animationId Id used to access the animation.
     * @param textureId Texture used for the animation.
     * @param row Sprite sheet row containing the animation frames.
     * @param width Width of each frame.
     * @param height Height of each frame.
     * @param numFrames Total number of animation frames.
     * @param frameSpeedRate Animation playback speed.
     * @param isLoop Determines whether the animation repeats.
     */
    void AddAnimation(
      const std::string& animationId,
      const std::string& textureId,
      int row,
      int width,
      int height,
      int numFrames,
      int frameSpeedRate,
      bool isLoop
    );
    /**
     * @brief Animation getter.
     *
     * @param animationId Id of the requested animation.
     * @return Animation data associated with the id.
     */
    AnimationData GetAnimation(const std::string& animationId);
};

#endif  // ANIMATIONMANAGER_HPP