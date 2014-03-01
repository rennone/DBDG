#ifndef DBDG_SPRITE_BATCHER_3D_H
#define DBDG_SPRITE_BATCHER_3D_H

//3Dで４点と,TextureRegionを渡すと描画してくれるクラス
#include "../math/Vector2.hpp"
#include "../math/Vector3.hpp"
#include "../Texture.h"

namespace DBDG
{
  class SpriteBatcher3D
  {
    float *verticesBuffer;
    unsigned int *indicesBuffer;
    int bufferIndex;
    int numSprite;
  public:
    SpriteBatcher3D(int _maxSprites);
    ~SpriteBatcher3D();  
  
    void beginBatch(Texture *texture);
  
    void drawSprite(const Vector3 position, const Vector3 &normal, const Vector2 &size, const TextureRegion *region);
    void drawSprite(const Vector3 position, const Vector3 &normal, const Vector2 &size, const float &angle, const TextureRegion *region);
//自分で,上と横野軸ベクトルを指定してから,描画できる
    void drawSprite(const Vector3 position, const Vector3 &rightAxis, const Vector3 &upAxis, const Vector2 &size, const TextureRegion *region);
    void endBatch() const;
  };
}
#endif
