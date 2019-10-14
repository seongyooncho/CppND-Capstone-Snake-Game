#include "controller.h"
#include <iostream>
#include <cmath>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.isAIEnabled())
    snake.setAI(false);
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, SDL_Point const &food) const {
  SDL_Event e;

  if (snake.isAIEnabled())
    ControlAI(snake, food);

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_SPACE:
          snake.setAI(!snake.isAIEnabled());
          break;

        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}

void Controller::ControlAI(Snake &snake, SDL_Point const &food) const
{
  Snake::Direction left;
  Snake::Direction right;
  switch(snake.direction)
  {
    case Snake::Direction::kUp:
      left = Snake::Direction::kLeft;
      right = Snake::Direction::kRight;
      break;
    case Snake::Direction::kRight:
      left = Snake::Direction::kUp;
      right = Snake::Direction::kDown;
      break;
    case Snake::Direction::kDown:
      left = Snake::Direction::kRight;
      right = Snake::Direction::kLeft;
      break;
    case Snake::Direction::kLeft:
      left = Snake::Direction::kDown;
      right = Snake::Direction::kUp;
      break;
  }
  if (TestMove(snake, snake.direction, food))
    return;
  else if (TestMove(snake, left, food))
    snake.direction = left;
  else if (TestMove(snake, right, food))
    snake.direction = right;
}

bool Controller::TestMove(Snake const &snake, Snake::Direction const &direction, SDL_Point const &food) const
{
  float head_x = snake.head_x;
  float head_y = snake.head_y;
  switch (direction) {
    case Snake::Direction::kUp:
      head_y -= snake.speed;
      break;

    case Snake::Direction::kDown:
      head_y += snake.speed;
      break;

    case Snake::Direction::kLeft:
      head_x -= snake.speed;
      break;

    case Snake::Direction::kRight:
      head_x += snake.speed;
      break;
  }
  head_x = fmod(head_x + snake.getGridWidth(), snake.getGridWidth());
  head_y = fmod(head_y + snake.getGridHeight(), snake.getGridHeight());

  int new_x = static_cast<int>(head_x);
  int new_y = static_cast<int>(head_y);

  // Check for collision
  for (auto const &item : snake.body) {
    if (new_x == item.x && new_y == item.y) {
      return false;
    }
  }

  int old_x = static_cast<int>(snake.head_x);
  int old_y = static_cast<int>(snake.head_y);

  // Check if will it not be farther
  int distance_now = abs(food.x - old_x) + abs(food.y - old_y);
  int distance_next = abs(food.x - new_x) + abs(food.y - new_y);
  return distance_next <= distance_now;
}
