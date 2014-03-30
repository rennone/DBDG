#ifndef DBDG_GL_LIGHTING_MANAGER_H
#define DBDG_GL_LIGHTING_MANAGER_H
/*
#include "../Color4.hpp"
#include "../math/Vector4.hpp"

namespace DBDG
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
  
  class GLLightingManager
  {
    enum struct COLOR
    {
      DIFFUSE,
        AMBIENT,
        SPECULAR
        };
    
    const unsinged int lightId[MAX_LIGHT_NUM];
    bool lightState[MAX_LIGHT_NUM];
  public:
    static constexpr unsigned int MAX_LIGHT_NUM = 8;
    static constexpr bool within(const unsigned int &id){
      return id>=0 && id<MAX_LIGHT_NUM;
    }
    static LightingManager* getInstance()
    {
      static LightingManager instance;
      return &instane;
    }
    bool setColor(const unsigned int &id, COLOR kind, const Color4 &color);
    bool killLight(const unsigned int &id);
    int getFreeLight();
    bool setLight(const unsigned int &id, const Vector4 &position, const Vector4 &direction);
  private:
    LightingManager();
    LightingManager(const LightingManager &other);    
    ~LightingManager();
    LightingManager& operator=(const LightingManager &other);
  };
}
*/
#endif
