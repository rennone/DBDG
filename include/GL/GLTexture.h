#ifndef DBDG_GL_TEXTURE_H
#define DBDG_GL_TEXTURE_H

#include "../Texture.h"
//ç°ÇÃèä.pngÉIÉìÉäÅ[
namespace DBDG
{

  class GLTexture:public DBDG::Texture
  {
    unsigned char *image;
    unsigned int texId;
  public:
    GLTexture(const std::string &fileName);
    ~GLTexture();
    void load(const std::string &fileName);
    void bind()const;
    void unbind()const;
  };
}

/*
class TextureAnimation
{
  std::vector<TextureRegion*> regions;
  const Texture* const texture;
  int index;
  bool repeat;
  float loopTime;
  float elapsedTime;
public:
TextureAnimation(Texture *_texture, float _loopTime)
  :texture(_texture), index(0), loopTime(_loopTime), elapsedTime(0)
  {
  }

  void start()
  {
    index = 0;
    elapsedTime = 0;
  }
  
  void addFrame(const TextureRegion *region)
  {
    regions.push_back(region);
  }

  void update(float delta)
  {
    elapsedTime+=delta;
    if(regions.size() == 0)
      return;
    if(elapsedTime > 1.0/region.size())
    {
      next();
      elapsedTime -= 1.0/region.size();
    }
  }
  
  void next()
  {
    if(repeat)
      index = (index+1)%regions.size();
    else
      index = min(regions.size()-1, index+1);
  }

  TextureRegion* frame() const
  {
    return regions[index];
  }

  void Repeat(bool _repeat)
  {
    repeat = _repeat;
  }

  bool isLast() const
  {
    return index == regions.size()-1;
  }

  int numFrame() const
  {
    return regions.size();
  }
};
*/

#endif
