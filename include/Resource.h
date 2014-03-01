#ifndef DBDG_RESOURCE_H
#define DBDG_RESOURCE_H

#include <string>
namespace DBDG
{
  //リソースフォルダへのパスを保持するクラス
  class Resource
  {
    std::string fileName;
    
    static std::string& PathToResource()
    {
      static std::string path = "";
      return path;    
    }

    Resource(const Resource &other);
    Resource& operator=(const Resource &other);
  protected :    
    Resource(std::string file_name)
      :fileName(file_name)
    {  }


  public:
    static void setPathToResource(std::string path)
    {
      PathToResource() = path;    
    }

    static std::string getPathToResource()
    {
      return PathToResource();
    }
  };
}
#endif
