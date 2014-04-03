#ifndef DBDG_AL_AUDIO_H
#define DBDG_AL_AUDIO_H

#include "../Audio.h"
#include "AL/alut.h"

namespace DBDG
{
  class ALSoundManager;
  class ALMusicManager;
  
  class ALAudio : public Audio
  {
    ALAudio(const ALAudio &other);
    ALAudio& operator=(const ALAudio& other);
  public:
    static ALAudio& getInstance()
    {
      static ALAudio instance;
      return instance;
    }
  ALAudio():Audio() { }
    ~ALAudio() {}
    SoundManager& getSoundManager() const;
    MusicManager& getMusicManager() const;
  };
}
#endif
