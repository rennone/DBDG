#ifndef DBDG_SPRITE_BATCHER_H
#define DBDG_SPRITE_BATCHER_H

#include "../Texture.h"
#include "../math/Vector2.hpp"

namespace DBDG
{
//2Dテクスチャをまとめて描画する為のクラス
  class SpriteBatcher
  {
    float *verticesBuffer;
    unsigned int *indicesBuffer;
    
    int bufferIndex;
    int numSprite;
  public:
    SpriteBatcher(int max_sprites);
    ~SpriteBatcher();
  
    void beginBatch(Texture *texture);
    void endBatch() const;

    void clearSprites();
    void drawAllSprites(const Texture *texture) const;

    void pushSprite(const float &center_x, const float &center_y, const float &width, const float &height, const TextureRegion *region);
    void pushSprite(const Vector2 &center, const Vector2 &size, const TextureRegion *region);
    void pushSprite(const float &center_x, const float &center_y, const float &width, const float &height, const float &angle, const TextureRegion *region);
    void pushSprite(const Vector2 &center, const Vector2 &size, const float &angle, const TextureRegion *region);
  };

  inline void SpriteBatcher::pushSprite(const Vector2 &center, const Vector2 &size, const TextureRegion *region)
  {
    pushSprite(center.x, center.y, size.x, size.y, region);
  }  

  inline void SpriteBatcher::pushSprite(const Vector2 &center, const Vector2 &size, const float &angle, const TextureRegion *region)
  {
    pushSprite(center.x, center.y, size.x, size.y, angle, region);
  }    
}


#endif
