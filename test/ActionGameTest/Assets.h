#ifndef ACTION_TEST_ASSETS_H
#define ACTION_TEST_ASSETS_H

#include <GL/glDBDG.h>
#include <AL/ALAudio.h>

class Assets
{
public:
  static DBDG::XfileModel *gargoyle;
  static DBDG::Sound *akan;
  static void loadAssets();
private:
  Assets();  
};

#endif
