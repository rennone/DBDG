#include <SpriteAnimation.h>
#include <cmath>
namespace DBDG
{ 
  SpriteAnimation::SpriteAnimation(const float &animation_time, const std::vector<TextureRegion*> &regions)
    :animationTime(animation_time)    
  {    
    frameNum = regions.size();
    frames = regions;
  }

  SpriteAnimation::SpriteAnimation(const float &animation_time, const std::vector<TextureRegion*> &&regions)
    :animationTime(animation_time)    
  {    
    frameNum = regions.size();
    frames = move(regions);
  }

  void SpriteAnimation::setLoop(const bool &loop)
  {
    isLoop = loop;
  }

  const TextureRegion* SpriteAnimation::getFrameSprite(const float &time) const
  {
    int frameIndex = floor(time/animationTime*frameNum);

    if (isLoop)
      frameIndex = frameIndex%frameNum;

    if( frameIndex<0 || frameIndex >= frameNum)
      return frames[frameNum-1];

    return frames[frameIndex];
  } 
}
