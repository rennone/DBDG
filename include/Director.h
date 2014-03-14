#ifndef DBDG_DIRECTOR_H
#define DBDG_DIRECTOR_H

namespace DBDG
{
  class Game;
  class Director
  {
    Game *game;
  public:
    Director(Game *game)
      :game(game)
    {}
    virtual ~Director(){}    
  };
}
#endif
