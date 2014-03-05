#include <GLFW/glfw3.h>
#include <GL/GLTexture.h>
#include <lodepng.h>
#include <vector>
#include <cstdlib>

namespace DBDG
{
  GLTexture::GLTexture(const std::string &fileName)
    :Texture(fileName)
  {
    load(fileName);
  }

  GLTexture::~GLTexture()
  {
  }
  
  void GLTexture::load(const std::string &fileName)
  {
    std::vector<unsigned char> raw_image;
    unsigned int width, height;

    std::string name   = Resource::getCurrentDirectory() + fileName;  
    unsigned int error = lodepng::decode(raw_image, width, height, name.c_str());   
  
    if(error != 0)
    {
      fprintf(stderr, "can not read file %s\n", name.c_str());
      //todo例外を投げるべき
      exit(2);
    }

    if( (width&(width-1)) != 0 || (height&(height-1)) != 0)
    {
      fprintf(stderr, "texture size must be power of 2\n");
      //todo例外を投げるべき
      exit(2);
    }

    this->width  = width;
    this->height = height;

    int size = width*height*4; //RGBAの4
    image = new unsigned char[size];
    memset(image, 0, sizeof(unsigned char)*size);	//0で初期化
  
    for(size_t i=0; i<size; i++)
      image[i] = raw_image[i];  

    glGenTextures(1, &texId);
    
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
    glEnable(GL_TEXTURE_2D);
  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);   
  }

  inline void GLTexture::bind() const
  {
    glBindTexture(GL_TEXTURE_2D, texId);
  }

  inline void GLTexture::unbind() const
  {
    glBindTexture(GL_TEXTURE_2D, 0);  
  }
}
