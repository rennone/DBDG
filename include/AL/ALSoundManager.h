#ifndef DBDG_AL_SOUND_MANAGER_H
#define DBDG_AL_SOUND_MANAGER_H

#include "../Audio.h"
#include "AL/alut.h"

namespace DBDG
{
  class ALSound : public Sound
  {
    ALuint buffer, source;
  public:
    ALSound(const std::string &file_name);
    void play();
    void dispose();
  };

  class ALSoundManager : public SoundManager
  {
    ALSoundManager() { }
    ~ALSoundManager() { };
  public:
    static ALSoundManager& getInstance()
    {
      static ALSoundManager instance;
      return instance;
    }

    Sound* newSound(const std::string &file_name);
  };
}
#endif
