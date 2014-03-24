#ifndef DBDG_MODEL_H
#define DBDG_MODEL_H

#include "Color3.hpp"
#include "Color4.hpp"
#include "math/Vector3.hpp"
#include "FileIO.h"
#include <string>

namespace DBDG
{
  class Model
  {    
  protected:
    std::string fileName;     //ファイル名を含めたフルパス
    std::string superiorPath; //ルートからこのファイルまでのパス
  public:
  Model(const std::string &file_name)
    :fileName(file_name)
    {
      superiorPath = FileIO::getSuperiorFolderPath(file_name);
    }
    virtual ~Model(){  }  
    virtual void render() const = 0;
    virtual void renderWithAlpha(const float &alpha) const = 0;
    virtual void renderWithColor3(const Color3 &color) const = 0;
    virtual void renderWithColor4(const Color4 &color) const = 0;
    virtual void load(const std::string&, const float&) = 0;
    virtual void dispose() = 0;
  };
}

#endif
