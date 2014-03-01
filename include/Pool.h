#ifndef DBDG_POOL_H
#define DBDG_POOL_H

//メモリプールのクラス
//PoolObjectFactoryクラスを継承して, 必要なクラスを生成するFactoryクラスを作成し, 引数として送る
#include <cstddef>
#include <stack>

namespace DBDG
{
  template<class T>
    class PoolObjectFactory
  {
  public:
    PoolObjectFactory(){}
    virtual ~PoolObjectFactory(){}
    virtual T* createObject()=0;                  //クラスを生成する
  };

  template<class T>
    class Pool
  {
    const int maxSize;
    std::stack<T*> freeObjects;
    PoolObjectFactory<T> *const factory;  
  public:  
  Pool( PoolObjectFactory<T> *_factory, int _maxSize)
    :maxSize(_maxSize), factory(_factory)
    {
    }

    ~Pool()
    {
      delete factory;
      while(!freeObjects.empty())
      {
        auto object = freeObjects.top();
        delete object;
        freeObjects.pop();
      }
    }

    T* newObject()
    {
      T* object = NULL;

      if(freeObjects.empty())
      {
        object = factory->createObject();
      }
      else
      {      
        object = freeObjects.top();
        freeObjects.pop();
      }
      return object;
    }

    void freeObject(T *object)
    {
      if(freeObjects.size() < maxSize)
        freeObjects.push(object);
      else
        delete object;    //再大容量を超えた場合はしょうがないので削除
    }
  };
}
#endif
