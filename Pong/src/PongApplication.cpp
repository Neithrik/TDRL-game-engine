#include <iostream>

#include <vector>
#include <stdlib.h>

#include "Tdrl.h"

class Pong : public tdrl::Application {
public:
  enum class Direction { UP, DOWN, LEFT, RIGHT, };

  Pong() : direction_(Direction::UP) {
	  snake_ = new tdrl::MultiPoints(tdrl::GameObject::Color::BLUE,
		  tdrl::CoordinateList({ tdrl::Coordinate(10, 10), tdrl::Coordinate(10, 11), tdrl::Coordinate(10, 12)
			  }));
	  apple_ = new tdrl::Point(tdrl::GameObject::Color::RED, tdrl::Coordinate(15, 15));
	  gameObjects_ = { snake_, apple_ };
  }

  ~Pong() {}

private:
  std::vector<tdrl::GameObject*>* GetGameObjects() override {
	  ChangeDirection();
	  MoveSnake();
	  CheckExit();
	  return &gameObjects_;
  }

  void ChangeDirection() {
	  switch (last_key_) {
	  case Key::LEFT:
		  switch (direction_) {
		  case Direction::UP:
			  direction_ = Direction::LEFT;
			  break;
		  case Direction::DOWN:
			  direction_ = Direction::RIGHT;
			  break;
		  case Direction::LEFT:
			  direction_ = Direction::DOWN;
			  break;
		  case Direction::RIGHT:
			  direction_ = Direction::UP;
			  break;
		  };
		  break;
	  case Key::RIGHT:
		  switch (direction_) {
		  case Direction::UP:
			  direction_ = Direction::RIGHT;
			  break;
		  case Direction::DOWN:
			  direction_ = Direction::LEFT;
			  break;
		  case Direction::LEFT:
			  direction_ = Direction::UP;
			  break;
		  case Direction::RIGHT:
			  direction_ = Direction::DOWN;
			  break;
		  break;
		  }
	  }
  }

  void MoveSnake() {
	  tdrl::CoordinateList snake_points = snake_->GetCoordinates();
	  tdrl::Coordinate head = *(snake_points.end() - 1);


	  tdrl::Coordinate new_head;

	  switch (direction_) {
	  case Direction::UP:
		  new_head = tdrl::Coordinate({ head.first, head.second + 1 });
		  break;
	  case Direction::DOWN:
		  new_head = tdrl::Coordinate({ head.first, head.second - 1 });
		  break;
	  case Direction::LEFT:
		  new_head = tdrl::Coordinate({ head.first - 1, head.second });
		  break;
	  case Direction::RIGHT:
		  new_head = tdrl::Coordinate({ head.first + 1, head.second });
		  break;
	  }

	  snake_points.push_back(new_head);

	  if (head == apple_->GetCoordinates()[0]) {
		  GenerateNewApple(snake_points);
	  }
	  else {
		  snake_points.erase(snake_points.begin());
	  }

	  snake_->SetCoordinates(snake_points);
  }

  void GenerateNewApple(tdrl::CoordinateList& snake_points) {
	  while (true) {
		  int newX = rand() % 50;
		  int newY = rand() % 50;

		  bool clash = false;
		  for (tdrl::Coordinate snake_point : snake_points) {
			  if (snake_point.first == newX && snake_point.second == newY) {
				  clash = true;
				  break;
			  }
		  }

		  if (!clash) {
			  apple_->SetPoint({ newX, newY });
			  return;
		  }
	  }
  }

  void CheckExit() {
	  tdrl::CoordinateList snake_points = snake_->GetCoordinates();
	  tdrl::Coordinate head = *(snake_points.end() - 1);

	  if (head.first < 0 || head.second < 0) {
		  Exit();
	  }

	  if (head.first >= 50 || head.second >= 50) {
		  Exit();
	  }
  }

  tdrl::MultiPoints* snake_;
  tdrl::Point* apple_;
  std::vector<tdrl::GameObject*> gameObjects_;
  Direction direction_;

};

tdrl::Application *tdrl::CreateApplication() { return new Pong(); }