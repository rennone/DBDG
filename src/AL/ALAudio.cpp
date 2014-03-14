#include <AL/ALAudio.h>
#include <AL/ALSoundManager.h>
#include <AL/ALMusicManager.h>
#include "AL/alut.h"

namespace DBDG
{
  SoundManager& ALAudio::getSoundManager() const
  {
    return ALSoundManager::getInstance();
  }
  
  MusicManager& ALAudio::getMusicManager() const
  {
    return ALMusicManager::getInstance();
  }
}
