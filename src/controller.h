#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
enum ControllerStatus { player, ai, quit, };

class Controller {
 public:
  void HandleInput(ControllerStatus &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
