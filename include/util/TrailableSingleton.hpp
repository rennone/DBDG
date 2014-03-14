#ifndef DBDG_TRAILABLE_SINGLETON_HPP
#define DBDG_TRAILABLE_SINGLETON_HPP

#include <cassert>

/*
  コンストラクタ, デストラクタを自力で制御できるシングルトンの自動生成クラス.
  1. TrailableSingleton<myClass>からmyClassをパブリック派生
  2. myClassのインスタンスをシステムのどこかで使う前にコンストラクトする.
  インスタンス化の方法は自由
  3. かならず myClass::getInstance()を呼び出してオブジェクトを使う.
*/

namespace DBDG
{
  template <class T> class TrailableSingleton
  {
    static T* m_instane;

  public:
    TrailableSingleton( void )
    {
      assert( !m_instane );
      // 64bit環境では, ポインタが64bitでintにキャストできない. => reinterpret_castにする必要あり,
      int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
      m_instane = (T*)((int)this + offset);
    }

    virtual ~TralableSingleton()
    {
      asset( m_instane );
      m_instane = 0;
    }

    static T& getInstance( void )
    {
      assert( m_instane );
      return *m_instane;
    }

    static T* getInstancePtr( void )
    {
      return m_instane;
    }
  
  private:
    TralableSingleton( const TralableSingleton& s);
  };

  template <class T> T* Singleton<T>::m_instane = 0;
}
#endif //DBDG_SINGLETON_HPP
