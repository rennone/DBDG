#ifndef DBDG_AL_MUSIC_MANAGER_H
#define DBDG_AL_MUSIC_MANAGER_H

#include "../Audio.h"
#include "AL/alut.h"

namespace DBDG
{
  class ALMusic : public Music
  {
    ALuint buffer, source;
  public:
    ALMusic(const std::string &file_name);
    void play();
    void dispose();
  };

  class ALMusicManager : public MusicManager
  {
    ALMusicManager() { }
    ~ALMusicManager() { };
  public:
    static ALMusicManager& getInstance()
    {
      static ALMusicManager instance;
      return instance;
    }

    Music* newMusic(const std::string &file_name);
  };
}

#endif
