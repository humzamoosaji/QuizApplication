#include "Player.h"

using namespace std;

Player::Player() {};
Player::Player(string name)
{
	this->name = name;
	this->score = 0;
}

int Player::getScore()
{
	return this->score;
}

string Player::getName()
{
	return this->name;
}

void Player::setName(string name)
{
	setName(name);
}

void Player::incrementScore()
{
	score++;
}

