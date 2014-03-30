#include <FileIO.h>
#include <cstdio>
#include <iostream>
namespace DBDG
{
  FILE* FileIO::fileOpen(const std::string file_name, const char* mode)
  {
    FILE* fp;
    const std::string name = rootDirectory + file_name;
    if( (fp= fopen( name.c_str(), mode)) == nullptr)
    {
      std::cerr << "can not open file " << name << std::endl;
      exit(2);
    }    
    return fp;
  }

  //static member
  std::string FileIO::getSuperiorFolderPath(const std::string str)
  {
    auto index = str.rfind("/");
    if(index == std::string::npos)
      return "";
    else
      return str.substr(0, index+1); //0からindex文字とってくる.
  }
}
