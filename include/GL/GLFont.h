#ifndef DBDG_GL_FONT_H
#define DBDG_GL_FONT_H

//ヘッダーファイルのインクルードは, ""で書いた方が良い
//外部から使うときに, そっちのmakeFileに書かれているパスに依存してしまうから
#include "../Font.h"
#include "../Color4.hpp"
#include "../math/Vector2.hpp"
#include "../math/Vector3.hpp"

/*
  // BitmapFontを使った, Fontクラス
  同時描画文字数をフォントごとに指定できるように描画用のSpriteBatcherを渡すようになっている.
  文字数で渡さないのは, 複数のフォント(のインスタンス)でSpriteBatcherを共有できるようにする為.
  全てのフォントで,最大文字数が同じで,SpriteBatcherを共有したい時は, 継承してクラス変数にbatcherをもたせて, 親のコンストラクタに渡せば良い
  // example
  class myGLFont : GLFont
  {
  public :
  static SpriteBatcher2D static_batcher2D;
  static SpriteBatcher3D static_batcher3D;
  myGLFont(...)
  :GLFont(texture, static_batcher2D, static_batcher3D)
  }
*/

namespace DBDG
{
  class Texture;
  class TextureRegion;
  class SpriteBatcher;
  class SpriteBatcher3D;
  class GLFont: public Font
  {
    Texture *texture;
    TextureRegion *glyphs[96];
    float glyphWidth, glyphHeight;
    float glyphHeightPerWidth;
    SpriteBatcher   *batcher2D;
    SpriteBatcher3D *batcher3D;
  public:
    //テクスチャ, fontが書かれている領域の左上, 一行あたりの文字数, 文字のサイズ
    GLFont(Texture *texture, SpriteBatcher *batcher2D, SpriteBatcher3D *batcher3D,
           const float &offsetX, const float &offsetY, const int &glyphsPerRow, const float &glyphWidth, const float &glyphHeight);
    ~GLFont();

    /*size = 文字の横幅*/
    void drawString(const std::string &str,const Vector2 &point, const float &size,
                    const Color4 &color, const enum Alignment &alignment);

    /*advance = 文字間隔 0だと全文字が同じ場所になる*/
    void drawString(const std::string &str,const Vector2 &point, const float &size, const float &advance, 
                    const Color4 &color, const enum Alignment &alignment); 

    /* batcherを渡して描画する.このメソッド内ではclearSprites, drawSpritesを呼ばない為, 使用者が呼ぶ必要がある.
       複数の文字列をまとめてGPUに送る事ができるが,全ての文字列で色が同じになる.  */
    void drawStringWithBatcher(const std::string &str, SpriteBatcher *batcher,
                               const Vector2 &point, const float &size,
                               const float &advance, const enum Alignment &alignment) const;

    //3D空間に文字を描画
    /* normal -> 文字の法線ベクトル size = 文字の横幅*/    
    void drawString3D(const std::string &str, const Vector3 &position,
                      const Vector3 &normal, const float &size,
                      const Color4 &color, const enum Alignment &alignment);

    /*advance = 文字間隔 0だと全文字が同じ場所になる*/
    void drawString3D(const std::string &str, const Vector3 &position,
                      const Vector3 &normal, const float &size,
                      const float &advance, const Color4 &color,
                      const enum Alignment &alignment);

    /* batcherを渡して描画する.このメソッド内ではclearSprites, drawSpritesを呼ばない為, 使用者が呼ぶ必要がある.
       複数の文字列をまとめてGPUに送る事ができるが,全ての文字列で色が同じになる.  */
    void drawString3DWithBatcher(const std::string &str, SpriteBatcher3D *batcher,
                                 const Vector3 &position, const Vector3 &normal,
                                 const float &size, const float &advance,
                                 const enum Alignment &alignment) const;
  };

  /* advance 無しの場合は, size分だけ前進する*/
  inline void GLFont::drawString
    (const std::string &str,const Vector2 &point, const float &size, const Color4 &color,
     const enum Alignment &alignment)
  {
    drawString(str, point,size, size, color, alignment); //文字間隔を指定しなければ, sizeにする.
  }

  inline void GLFont::drawString3D
    (const std::string &str,const Vector3 &position, const Vector3 &normal,const float &size,
     const Color4 &color, const enum Alignment &alignment)
  { 
    drawString3D(str, position, normal,size, size, color, alignment); //文字間隔を指定しなければ, sizeにする.
  }

}


#endif

