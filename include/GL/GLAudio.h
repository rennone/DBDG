#ifndef DBDG_GL_AUDIO_H
#define DBDG_GL_AUDIO_H

//ヘッダーファイルのインクルードは, ""で書いた方が良い
//外部から使うときに, そっちのmakeFileに書かれているパスに依存してしまうから
#include "../Audio.h"
namespace DBDG
{
  class GLAudio : public Audio
  {  
  };
}
#endif
