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
      status = ActorStatus::Action;
    }

    Actor::~Actor()
    {
    }
    
    void Actor::render(const float &deltaTime)
    {
      for( auto child : children)
      {    
        if(child->status == ActorStatus::Action || child->status == ActorStatus::RenderOnly)
          child->render(deltaTime);
      }
    }

    void Actor::update(const float &deltaTime)
    {
      for( auto &child : children)
      {    
        if(child->status == ActorStatus::Action || child->status == ActorStatus::UpdateOnly)
          child->update(deltaTime);   
      }                
    }

    void Actor::checkStatus()
    {
      if(status == ActorStatus::Dead)
      {
        for( auto &child : children)
          child->setStatus(ActorStatus::Dead);
      }

      for( auto &child : children)
        child->checkStatus();

      //Deadステータスを削除し
      auto end_it = remove_if(children.begin(),
                              children.end(),
                              []( std::shared_ptr<Actor> p) -> bool
                              { return p->getStatus() == ActorStatus::Dead; });  
      children.erase(end_it, children.end());
    }

    void Actor::addChild(std::shared_ptr<Actor> child)
    { 
      children.push_back(child);
    }

//idで探索
    std::shared_ptr<Actor> Actor::searchChild(const int &id)
    {
      if(this->m_Id == id)
        return std::shared_ptr<Actor>(this);

      for(const auto &child : children)
      {
        auto res = child->searchChild(id);
        if(res != nullptr)
          return res;
      }
  
      return nullptr;
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
