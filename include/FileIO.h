#infndef DBDG_FILE_IO_H
#define DBDG_FILE_IO_H

#include <string>
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

    FileIO(const std::string &root_directory)
      :
    {
      
    }
    
    FileIO(const Resource &other);
    FileIO& operator=(const Resource &other);
  public:
    static FileIO* getInstance()
    {
      FileIO instance;
      return &instance;
    }

    FILE* openFile(const std::string file_name)
    {
      return NULL; 
    }
    
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
