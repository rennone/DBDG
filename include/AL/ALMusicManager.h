#ifndef DBDG_AL_MUSIC_MANAGER_H
#define DBDG_AL_MUSIC_MANAGER_H

#include "../Audio.h"
#include "AL/alut.h"

namespace DBDG
{
  class ALMusicManager;
  class ALMusic : public Music
  {
    friend class ALMusicManager;
    ALuint buffer, source;
  public:
    ALMusic(const std::string &file_name);
    void play();
    void dispose();
  };

  class ALMusicManager : public MusicManager
  {
    ALMusicManager():MusicManager() { }
    ~ALMusicManager() { };
    ALMusicManager(const ALMusicManager &other);
    ALMusicManager& operator=(const ALMusicManager &other);
  public:
    static ALMusicManager& getInstance()
    {
      static ALMusicManager instance;
      return instance;
    }

    Music* newMusic(const std::string &file_name) const;
  };
}

#endif
