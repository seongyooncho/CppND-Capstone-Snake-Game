#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, SDL_Point const &food) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  void ControlAI(Snake &snake, SDL_Point const &food) const;
  bool TestMove(Snake const &snake, Snake::Direction const &direction, SDL_Point const &food) const;
};

#endif
