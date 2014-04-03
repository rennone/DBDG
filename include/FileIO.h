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
    
    FileIO()
      :rootDirectory("")
    { }
    
    FileIO(const FileIO &other);
    FileIO& operator=(const FileIO &other);
    
  public:
    static FileIO& getInstance()
    {
      static FileIO instance;
      return instance;
    }

    FILE* fileOpen(const std::string file_name, const char* mode);

    void setRootDirectory(const std::string &root) {
      rootDirectory = root;
    }

    std::string getRootDirectory() {
      return rootDirectory;
    }

    // "/"文字より前の文字列を取得する
    static std::string getSuperiorFolderPath(const std::string str);
  };
}


#endif
