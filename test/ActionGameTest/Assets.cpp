#include "Assets.h"

DBDG::XfileModel* Assets::gargoyle = NULL;
DBDG::Sound* Assets::akan = NULL;

void Assets::loadAssets()
{
  gargoyle = new DBDG::XfileModel("resource/gargoyle/gargoyle.x", 1);
  akan = DBDG::ALAudio::getInstance().getSoundManager().newSound("resource/Akan00.wav");
}
