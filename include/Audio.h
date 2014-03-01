#ifndef DBDG_AUDIO_H
#define DBDG_AUDIO_H

#include <string>
namespace DBDG
{
  class Audio
  {
  public:  
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
  
    Music* newMusic(std::string fileName);
    Sound* newSound(std::string fileName);
  };
}
#endif
