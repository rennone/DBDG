#ifndef DBDG_AUDIO_H
#define DBDG_AUDIO_H

#include <string>
namespace DBDG
{
  
  class Music
  {
  public:
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
    virtual void play()=0;
    virtual void dispose()=0;
  };

  class SoundManager
  {
  public:
    virtual Sound* newSound(const std::string &fileName) = 0;    
  };

  class MusicManager
  {
  public:
    virtual Music* newMusic(const std::string &fileName) = 0;
  };
  
  class Audio
  {
  public:
    virtual SoundManager& getSoundManager() const = 0;
    virtual MusicManager& getMusicManager() const = 0;
  };
}
#endif
