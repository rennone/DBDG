#ifndef DBDG_AUDIO_H
#define DBDG_AUDIO_H

#include <string>
namespace DBDG
{
  
  class Music
  {
  public:
    virtual ~Music(){}
    virtual void play()=0;
    virtual void stop()=0;
    virtual void pause()=0;
    virtual void setLooping(bool looping)=0;
    virtual void setVolume(float volume)=0;
    virtual const bool isPlaying() const =0;
    virtual const bool isLooping() const =0;
    virtual void dispose()=0;
  };

  class Sound
  {
  public:
    virtual ~Sound(){}
    virtual void play()=0;
    virtual void dispose()=0;
  };

  class SoundManager
  {
    SoundManager(const SoundManager&);
    SoundManager& operator=(const SoundManager&);
  public:
    SoundManager(){}
    virtual ~SoundManager(){}
    virtual Sound* newSound(const std::string &fileName) const = 0;
  };

  class MusicManager
  {
    MusicManager(const MusicManager&);
    MusicManager& operator=(const MusicManager&);
  public:
    MusicManager(){}
    virtual ~MusicManager(){}
    virtual Music* newMusic(const std::string &fileName) const = 0;
  };
  
  class Audio
  {
    Audio(const Audio &);
    Audio& operator=(const Audio &);
  public:
    Audio(){}
    virtual ~Audio(){}
    virtual const SoundManager& getSoundManager() const = 0;
    virtual const MusicManager& getMusicManager() const = 0;
  };
}
#endif
