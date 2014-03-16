#ifndef DBDG_LOCK_H
#define DBDG_LOCK_H

/*
//スレッドのロック, アンロックをするクラス
//pthreadで実装
#include <pthread.h>
namespace DBDG
{
  class Lock
  {
    pthread_mutex_t *mtx;
  public:
    //コンストラクタでロックする
    explicit Lock(pthread_mutex_t *pm)
      :mtx(pm)
    {
      pthread_mutex_lock(mtx);
    }

    //デストラクタでアンロックする
    ~Lock()
    {
      pthread_mutex_unlock(mtx);    
    }
  };
}
*/

#endif
