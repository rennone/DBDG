#ifndef DBDG_MATRIX_H
#define DBDG_MATRIX_H

namespace DBDG
{
  class matrix33;
  class matrix44;
  
  template< class Mtx, unsigned N > struct IdMtx
  {
    static inline void eval( Mtx& mtx )
    {
      IdMtxImpl< Mtx, N, 0, 0, 0 >::eval( mtx );
    }
  };

  template< class Mtx, unsigned N, unsigned C, unsigned R, unsigned I>
  struct IdMtxImpl
  {
    enum
    {
      NxtI = I+1;
      NxtR = NxtI % N;     //行
      NxtC = NxtI / N % N; //列
    };

    static inline void eval( Mtx& mtx )
    {
      mtx[C][R] = (C==R) ? 1.0 : 0.0;
      IdMtxImpl< Mtx, N, NxtC, NxtR, NxtI >::eval( mtx );
    }
  };

  template<> struct IdMtxImpl< matrix33, 3, 0, 0, 3*3 >
  {
    static inline void eval( matrix33 ){};
  };

  template<> struct IdMtxImpl< matrix44, 4, 0, 0, 4*4 >
    {
      static inline void eval( matrix44 ){};
  };
    
}

#endif
