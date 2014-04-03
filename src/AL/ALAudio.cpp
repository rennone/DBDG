#include <AL/ALAudio.h>
#include <AL/ALSoundManager.h>
#include <AL/ALMusicManager.h>
#include "AL/alut.h"

namespace DBDG
{
  ALAudio::ALAudio()
    :Audio()
  {
  }
  
  ALAudio::~ALAudio()
  {
  }
  
  const SoundManager& ALAudio::getSoundManager() const
  {
    return ALSoundManager::getInstance();
  }
  
  const MusicManager& ALAudio::getMusicManager() const
  {
    return ALMusicManager::getInstance();
  }
}
