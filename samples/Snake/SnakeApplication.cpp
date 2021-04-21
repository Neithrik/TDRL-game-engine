#include <iostream>

#include <vector>
#include <stdlib.h>

#include "src/Tdrl.h"

constexpr int FIELD_SIZE = 20;

class Snake : public tdrl::Application {
public:

  enum class Direction { UP, DOWN, LEFT, RIGHT, };

  Snake() : direction_(Direction::UP) {
	  snake_ = new tdrl::MultiPoints(tdrl::GameObject::Color::BLUE,
		  tdrl::CoordinateList({
			  tdrl::Coordinate(10, 9),
			  tdrl::Coordinate(10, 10), 
			  tdrl::Coordinate(10, 11), 
			  tdrl::Coordinate(10, 12),
			  }));
	  apple_ = new tdrl::Point(tdrl::GameObject::Color::RED, tdrl::Coordinate(15, 15));
	  gameObjects_ = { snake_, apple_ };
	  agent_ = new tdrl::Agent(14, 3);
	  agent_->Init();
  }

  ~Snake() {}

private:
  std::vector<tdrl::GameObject*>* GetGameObjects() override {
	  ChangeDirection();
	  if (!MoveSnake()) {
		  return nullptr;
	  }
	  if (CheckExit()) {
		  return nullptr;
	  }
	  return &gameObjects_;
  }

  int* GetState() {
	  auto snake_points = snake_->GetCoordinates();
	  tdrl::Coordinate head = *(snake_points.end() - 1);
	  auto apple_point = apple_->GetCoordinates()[0];

	  int first_up = head.first < apple_point.first ? 1 : 0;
	  int first_mid = head.first == apple_point.first ? 1 : 0;
	  int first_down = head.first > apple_point.first ? 1 : 0;
	  int second_up = head.second < apple_point.second ? 1 : 0;
	  int second_mid = head.second == apple_point.second ? 1 : 0;
	  int second_down = head.second > apple_point.second ? 1 : 0;

	  int dir_left = direction_ == Direction::LEFT ? 1 : 0;
	  int dir_right = direction_ == Direction::RIGHT ? 1 : 0;
	  int dir_up = direction_ == Direction::UP ? 1 : 0;
	  int dir_down = direction_ == Direction::DOWN ? 1 : 0;

	  int danger_left = 0;
	  int danger_right = 0;
	  int danger_up = 0;
	  int danger_down = 0;

	  if (head.first == 0) {
		  danger_left = 1;
	  }
	  if (head.first == FIELD_SIZE - 1) {
		  danger_right = 1;
	  }
	  if (head.second == 0) {
		  danger_down = 1;
	  }
	  if (head.second == FIELD_SIZE - 1) {
		  danger_up = 1;
	  }

	  for (int i = 0; i < snake_points.size() - 2; i++) {
		  tdrl::Coordinate snake_point = snake_points[i];
		  if (head.first == snake_point.first + 1 && head.second == snake_point.second) {
			  danger_left = 1;
		  }
		  if (head.first == snake_point.first - 1 && head.second == snake_point.second) {
			  danger_right = 1;
		  }
		  if (head.first == snake_point.first && head.second == snake_point.second + 1) {
			  danger_down = 1;
		  }
		  if (head.first == snake_point.first && head.second == snake_point.second - 1) {
			  danger_up = 1;
		  }
	  }

	  int state[14] = { 
		  first_up, first_mid, first_down, second_up, second_mid, second_down,
		  dir_left, dir_right, dir_up, dir_down,
		  danger_left, danger_right, danger_up, danger_down};

	  for (int i = 0; i < 14; i++) {
		  std::cout << state[i] << ", ";
	  }
	  std::cout << std::endl;

	  return state;
  }

  void ChangeDirection() {
	  int action = agent_->GetAction(GetState(), 0.25);

	  switch (action) {
	  case 0:
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
	  case 2:
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

  bool MoveSnake() {
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

	  for (tdrl::Coordinate snake_point : snake_points) {
		  if (snake_point == new_head) {
			  return false;
		  }
	  }

	  snake_points.push_back(new_head);

	  if (head == apple_->GetCoordinates()[0]) {
		  GenerateNewApple(snake_points);
	  }
	  else {
		  snake_points.erase(snake_points.begin());
	  }

	  snake_->SetCoordinates(snake_points);

	  return true;
  }

  void GenerateNewApple(tdrl::CoordinateList& snake_points) {
	  while (true) {
		  int newX = rand() % FIELD_SIZE;
		  int newY = rand() % FIELD_SIZE;

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

  bool CheckExit() {
	  tdrl::CoordinateList snake_points = snake_->GetCoordinates();
	  tdrl::Coordinate head = *(snake_points.end() - 1);

	  if (head.first < 0 || head.second < 0) {
		  return true;
	  }

	  if (head.first >= FIELD_SIZE || head.second >= FIELD_SIZE) {
		  return true;
	  }

	  return false;
  }

  tdrl::MultiPoints* snake_;
  tdrl::Point* apple_;
  std::vector<tdrl::GameObject*> gameObjects_;
  Direction direction_;
  tdrl::Agent* agent_;
};

tdrl::Application *tdrl::CreateApplication() { return new Snake(); }