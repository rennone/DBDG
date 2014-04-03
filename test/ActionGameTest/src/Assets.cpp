#include "Assets.h"
#include <GL/glDBDG.h>

DBDG::Model* Assets::gargoyle = NULL;
DBDG::Sound* Assets::akan = NULL;
DBDG::SpriteAnimation* Assets::animation = nullptr;
void Assets::loadAssets()
{
  std::string gar = "resource/gargoyle/gargoyle.x";
  std::string tes = "resource/dragon.x";
  gargoyle =  DBDG::GLGraphic::getInstance().getModelManager().newModel(tes, 1);
  akan     = DBDG::ALAudio::getInstance().getSoundManager().newSound("resource/Akan00.wav");

  auto texture = DBDG::GLGraphic::getInstance().getTextureManager().newTexture("resource/fieldAtlas.png");
  std::vector<DBDG::TextureRegion*> region;

  int size = 64;
  auto create = [&size](DBDG::Texture* tex, int i, int j, int w, int h)->DBDG::TextureRegion*
    {      
      return new DBDG::TextureRegion(tex, i*size, j*size, w*size, h*size);
    };

  for(int i=0; i<10; i++)
  {
    region.push_back(create(texture, i, 0, 1, 1));
  }

  animation = new DBDG::SpriteAnimation(3.0, move(region));
  animation->setLoop(true);
}
