#ifndef UTIL_ACTOR_H
#define UTIL_ACTOR_H

#include <vector>
namespace DBDG
{
  class GLGame;
  namespace Util
  {
    class Actor
    {
    public:
      enum ActorStatus
      {
        Action,
        UpdateOnly,
        RenderOnly,
        NoUse,
        Dead
      };
  
      Actor(DBDG::GLGame *glGame);
      virtual ~Actor();
      virtual void render(const float &deltaTime);
      virtual void update(const float &deltaTime);
      virtual void checkStatus();
  
      virtual void addChild(Actor* child);
    
      enum ActorStatus getStatus() const;
      void setStatus(const enum ActorStatus &status);  
      const std::vector<Actor*>& getChildren() { return children; }

      Actor* searchChild(const int &id);
    
    protected:
      DBDG::GLGame* const glGame;
      std::vector<Actor*> children;
      enum ActorStatus status;
      unsigned int m_Id;
  
    private:
      static unsigned int s_Id;
    };
  }
}
#endif
