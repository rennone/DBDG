#include <GL/util/glDBDGUtil.h>
#include <GL/util/Actor.h>

namespace DBDG
{
  namespace Util
  {
    unsigned int Actor::s_Id = 0;

    Actor::Actor(GLGame *glGame)
      :glGame(glGame)
      ,m_Id(s_Id++)
    {
      status = Actor::Action;
    }

    Actor::~Actor()
    {
    }
    
    void Actor::render(const float &deltaTime)
    {
      for( auto child : children)
      {    
        if(child->status == Actor::Action || child->status == Actor::RenderOnly)
          child->render(deltaTime);
      }
    }

    void Actor::update(const float &deltaTime)
    {
      for( auto &child : children)
      {    
        if(child->status == Actor::Action || child->status == Actor::UpdateOnly)
          child->update(deltaTime);   
      }                
    }

    void Actor::checkStatus()
    {
      if(status == Actor::Dead)
      {
        for( auto &child : children)
          child->setStatus(Actor::Dead);
      }

      for( auto &child : children)
        child->checkStatus();

      //Deadステータスを削除し, NULLを入れる
      for( auto &child : children)
      {    
        if(child->getStatus() == Actor::Dead)
        {      
          delete child;
          child = NULL;
        }    
      }
      //NULLの要素を削除
      auto end_it = remove_if(children.begin(), children.end(),
                              [](Actor* p) -> bool { return p == NULL; });  
      children.erase(end_it, children.end());
    }

    void Actor::addChild(Actor* child)
    { 
      children.push_back(child);
    }

//idで探索
    Actor* Actor::searchChild(const int &id)
    {
      if(this->m_Id == id)
        return this;

      for(const auto &child : children)
      {
        auto res = child->searchChild(id);
        if(res != NULL)
          return res;
      }
  
      return NULL;
    }

    enum Actor::ActorStatus Actor::getStatus() const
    {
      return status;
    }
        
    void Actor::setStatus(const enum ActorStatus &status)
    {
      this->status = status;
    }
  }
}
