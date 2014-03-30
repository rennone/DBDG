#ifndef UTIL_ACTOR_H
#define UTIL_ACTOR_H

#include <vector>
#include <memory>

namespace DBDG
{
  class GLGame;
  namespace Util
  {
    class Actor
    {
    public:
      enum struct ActorStatus
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
      virtual void addChild(std::shared_ptr<Actor> child);
      enum ActorStatus getStatus() const;
      void setStatus(const enum ActorStatus &status);
      const std::vector<std::shared_ptr<Actor>>& getChildren() { return children; }
      std::shared_ptr<Actor> searchChild(const int &id);
      std::shared_ptr<Actor> searchChild(const std::string &tag);
      void setTag(const std::string &tag);
      std::string getTag() const;
    protected:
      DBDG::GLGame* const glGame;
      std::vector<std::shared_ptr<Actor>> children;
      enum ActorStatus status;
      unsigned int m_Id;
      std::string tag;
    private:
      static unsigned int s_Id;
    };
  }
}
#endif
