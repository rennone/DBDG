#ifndef DBDG_AL_SOUND_MANAGER_H
#define DBDG_AL_SOUND_MANAGER_H

#include "../Audio.h"
#include "AL/alut.h"

namespace DBDG
{
  class ALSoundManager;
  
  class ALSound : public Sound
  {
    friend class ALSoundManager;
    ALuint buffer, source;
    ALSound(const std::string &file_name);
  public:
    void play();
    void dispose();
  };

  class ALSoundManager : public SoundManager
  {
  ALSoundManager():SoundManager() { }
    ~ALSoundManager() { };
    ALSoundManager(const ALSoundManager &other);
    ALSoundManager& operator=(const ALSoundManager &other);
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
