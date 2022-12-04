#include "player.h"
#include <string>

Player::Player(string n, int p) : name(n), points(p) {}

void Player::setPoint(int p)
{
  points = points + p;
}

int Player::getPoints()
{
  return points;
}
