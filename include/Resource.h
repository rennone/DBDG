#ifndef DBDG_RESOURCE_H
#define DBDG_RESOURCE_H

#include <string>
namespace DBDG
{
  //リソースフォルダへのパスを保持するクラス
  class Resource
  {
    std::string fileName;    

    static std::string& CurrentDirectory()
    {
      static std::string dir = "";
      return dir;    
    }

    Resource(const Resource &other);
    Resource& operator=(const Resource &other);
  protected :    
    Resource(std::string file_name)
      :fileName(file_name)
    {  }

  public:
    static void setCurrentDirectory(std::string path)
    {
      CurrentDirectory() = path;
    }

    static std::string getCurrentDirectory()
    {
      return CurrentDirectory();
    }    

    static std::string getSuperiorFolderPath(const std::string str)
    {
      auto index = str.rfind("/");
      if(index == std::string::npos)
        return "";
      else
        return str.substr(0, index+1); //0からindex文字とってくる.
    }
  };
}
#endif
