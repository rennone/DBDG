#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <vector>
#include "Texture.h"

namespace DBDG
{
  class SpriteAnimation
  {
    std::vector<TextureRegion*> frames;
    const float animationTime;
    int frameNum;
    bool isLoop;
  public:
    SpriteAnimation(const float &animation_time, const std::vector<TextureRegion*> &regions);
    SpriteAnimation(const float &animation_time, const std::vector<TextureRegion*> &&regions);
    void setLoop(const bool &loop);
    TextureRegion* getFrameSprite(const float &time);
  };
}
#endif
