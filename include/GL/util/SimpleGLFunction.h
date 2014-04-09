#ifndef DBDG_GL_UTIL_SIMPLE_GL_FUNCTION
#define DBDG_GL_UTIL_SIMPLE_GL_FUNCTION

namespace DBDG
{
    //Utilでネストするとなぜかリンクエラーが起きる(ライブラリ生成時ではなく, ゲームコンパイル時に)
//  namespace Util
//  {
    extern void dbdgDrawAxis(const int &length);
    extern void dbdgDrawGrid(const int &gridSize, const int &xNum, const int &zNum);
//  }
}

#endif
