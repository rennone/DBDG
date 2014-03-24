#ifndef DBDG_FILE_IO_H
#define DBDG_FILE_IO_H

#include <string>
#include <memory>

namespace DBDG
{
  //リソースフォルダへのパスを保持するクラス
  class FileIO 
  {
    std::string rootDirectory;
    
    static std::string& CurrentDirectory()
    {
      static std::string dir = "";
      return dir;    
    }

    FileIO()
      :rootDirectory("")
    { }
    
    FileIO(const FileIO &other);
    FileIO& operator=(const FileIO &other);
  public:
    static FileIO* getInstance()
    {
      static FileIO instance;
      return &instance;
    }

    FILE* fileOpen(const std::string file_name, const char* mode);

    void setRootDirectory(const std::string &root)
    {
      rootDirectory = root;
    }

    std::string getRootDirectory()
    {
      return rootDirectory;
    }

    // "/"文字より前の文字列を取得する
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
