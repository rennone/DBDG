#ifndef DBDG_GL_LIGHT_MANAGER_H
#define DBDG_GL_LIGHT_MANAGER_H

#include "../../Color4.hpp"
#include "../../math/Vector4.hpp"

namespace DBDG
{
  namespace Util
  {
    struct GLLight
    {
      Vector3 position;
      Vector3 direction;
      Color4 diffuse;
      Color4 specular;
      Color4 ambient;
      unsigned short cutoff    = 180; //放射角度 0~90 or 180
      float constantAttenuation  = 1; //一定減衰率 0~1
      float linearAttenuation    = 0; //線形減衰率 0~1
      float quadraticAttenuation = 0; //2次減衰率
      bool enable = false;
    };
  
    class LightManager
    {
    public:
      enum struct LightColor
      {
        Diffuse,
          Ambient,
          Specular
          };
    
      static constexpr unsigned int MAX_LIGHT_NUM = 8;


      static LightManager* getInstance()
      {
        static LightManager instance;
        return &instance;
      }
    
      static constexpr bool within(const int &id){
        return id<MAX_LIGHT_NUM;
      }

      bool setLightPos(const int &id, const Vector3 &position, const Vector3 &direction);
      bool setLightColor(const int &id, LightColor kind, const Color4 &color);
      bool killLight(const int &id);
      void killAllLight();
      int getFreeLight() const;

    private:
      unsigned int lightState; //各ビットが使用中かを表す. 1=使用中
      unsigned int lightId[MAX_LIGHT_NUM]; //idとGL_LIGHT_の対応テーブル
    
      LightManager();
      LightManager(const LightManager &other);    
      ~LightManager();
      LightManager& operator=(const LightManager &other);
    };
  }
}

#endif
