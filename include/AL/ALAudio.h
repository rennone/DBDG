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
    //コピー不可にする
    ALAudio(const ALAudio &other);
    ALAudio& operator=(const ALAudio& other);
  public:
    static ALAudio& getInstance()
    {
      static ALAudio instance;
      return instance;
    }
    ALAudio();
    ~ALAudio();
    const SoundManager& getSoundManager() const;
    const MusicManager& getMusicManager() const;
  };
}
#endif
