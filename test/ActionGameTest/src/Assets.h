#ifndef ACTION_TEST_ASSETS_H
#define ACTION_TEST_ASSETS_H

#include <GL/glDBDG.h>
#include <AL/ALAudio.h>

class Assets
{
public:
  static DBDG::Model *gargoyle;
  static DBDG::Sound *akan;
  static DBDG::SpriteAnimation *animation;
  
  static void loadAssets();

private:
  Assets();  
};

#endif
