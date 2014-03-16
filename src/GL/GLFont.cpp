#include <Texture.h>
#include <GL/glDBDG.h>
#include <GL/GLFont.h>

namespace DBDG
{
  GLFont::GLFont(Texture *texture,
                 SpriteBatcher *batcher2D, SpriteBatcher3D *batcher3D,
                 const float &offsetX, const float &offsetY, const int &glyphsPerRow, const float &glyphWidth, const float &glyphHeight)
    :texture(texture)
    ,batcher2D(batcher2D)
    ,batcher3D(batcher3D)
    ,glyphWidth(glyphWidth)
    ,glyphHeight(glyphHeight)
    ,glyphHeightPerWidth(glyphHeight/glyphWidth)    
  {
    for(int i=0; i<96; i++)
    {
      int x = offsetX + (i%glyphsPerRow)*glyphWidth;
      int y = offsetY + floor(i/glyphsPerRow)*glyphHeight;
      glyphs[i] = new TextureRegion(texture, x ,y ,glyphWidth ,glyphHeight);
    }
  }

  void GLFont::drawString(const std::string &str,
                          const Vector2 &point,
                          const float &size, /*文字サイズ 横幅*/
                          const float &advance, /*文字間隔 */
                          const Color4 &color,
                          const enum Alignment &alignment)
  {
    glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT | GL_ENABLE_BIT);
    glColor4f(color.r, color.g, color.b, color.a);
    glDisable(GL_LIGHTING);
    batcher2D->clearSprites();
    drawStringWithBatcher(str, batcher2D, point, size, advance, alignment);
    batcher2D->drawAllSprites(texture);
    
    glPopAttrib();
  }

  // size : 横幅, advance : 文字間隔 0の場合は全て同じ場所に描画される.
  void GLFont::drawStringWithBatcher( const std::string &str,SpriteBatcher *batcher, const Vector2 &point,
                          const float &size, const float &advance,
                          const enum Alignment &alignment) const
  {    
    float x = point.x + size/2;
    //alignmentにより開始位置を変更
    switch(alignment)
    {
    case ALIGNMENT_RIGHT:
      x -= advance*(str.size()-1);
      break;
    case ALIGNMENT_CENTER:
      x -= advance*(str.size()-0.5)/2;
      break;      
    case ALIGNMENT_LEFT :    
    default:
      break;
    }

    for(int i=0; i<str.size(); i++)
    {
      const int c = str[i] - ' ';
      if(c<0 || c > 95)
        continue;
      
      //縦幅はアスペクト比でそろえて描画する.
      batcher->pushSprite(x, point.y, size, size*glyphHeightPerWidth, glyphs[c]);
      x += advance;
    }
  }

  //3D空間に描画

    //3D空間に描画
  void GLFont::drawString3D( const std::string &str,
                             const Vector3 &position,
                             const Vector3 &normal,
                             const float &size, const float &advance,
                             const Color4 &color, const enum Alignment &alignment)
  {
    glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT | GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glColor4f(color.r, color.g, color.b, color.a);
    
    batcher3D->clearSprites();
    drawString3DWithBatcher(str, batcher3D, position, normal, size, advance, alignment);
    batcher3D->drawAllSprites(texture);
    
    glPopAttrib();
  }
  
  void GLFont::drawString3DWithBatcher( const std::string &str, SpriteBatcher3D *batcher,
                                        const Vector3 &position, const Vector3 &normal,
                                        const float &size, const float &advance,
                                        const enum Alignment &alignment) const
  {
    const Vector3 up(0,1,0);  
    auto axis1 = up.cross(normal);
    axis1.normalize();
    auto axis2 = normal.cross(axis1);
    axis2.normalize();
    
    auto delta = advance*axis1;    
    auto left = position-axis1*size/2;
    
    switch(alignment)
    {
    case ALIGNMENT_RIGHT:
      left -= (str.size()-0.5)*delta;
      break;
    case ALIGNMENT_CENTER:
      left -= (str.size()-0.5)/2*delta;
      break;      
    case ALIGNMENT_LEFT :
    default:
      break;
    }
    
    for(int i=0; i<str.size(); i++)
    {
      const int c = str[i] - ' ';
      if(c<0 || c > 95)
        continue;
      
      batcher->pushSprite( left, axis1, axis2, Vector2(size, size), glyphs[c]);
      left += delta;
    }
  }

}

