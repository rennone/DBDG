#include <AL/ALSoundManager.h>
#include <AL/AL/alut.h>
#include <Resource.h>

namespace DBDG
{
  //--------------------Sound Class--------------------//
  ALSound::ALSound(const std::string &file_name)
  {
    const auto name = Resource::getCurrentDirectory() + file_name;
    buffer = alutCreateBufferFromFile(name.c_str());
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
  }

  void ALSound::play()
  {
    alSourcePlay(source);
  }

  //TODO not implemented
  void ALSound::dispose()
  {
  }

  Sound* ALSoundManager::newSound(const std::string &file_name) const
  {
    return new ALSound(file_name);
  }
  
}
