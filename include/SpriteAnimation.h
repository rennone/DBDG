#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <cmath>
#include "Texture.h"
namespace DBDG
{
  class SpriteAnimation
  {
    TextureRegion *frames;
    float animationTime;
    int frameNum;
    bool isLoop;
  public:
    SpriteAnimation(TextureRegion* regions, ...);
    void setLoop(const bool &loop);
    void setAnimationTime(const float &time);
    TextureRegion* getFrameSprite(const float &time);
  };

  SpriteAnimation::SpriteAnimation(TextureRegion* region, float )
  {
    frames = region;
    frameNum = sizeof(region)/sizeof(region[0]);
  }

  void SpriteAnimation::setAnimationTime(const float &time)
  {
    animationTime = time;
  }
  
  void SpriteAnimation::setLoop(const bool &loop)
  {
    isLoop = loop;
  }

  TextureRegion* getFrameSprite(const float &time)
  {
    int frameIndex = floor(time/animationTime*frameNum);

    if (isLoop)
      frameIndex = frameIndex%frameNum;

    if( frameIndex<0 || frameIndex >= frameNum)
      return NULL;

    return frames[frameIndex];
  }
}
#endif
