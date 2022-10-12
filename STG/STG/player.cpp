#include"player.h"
#include"dxlib.h"

Player::Player(Location loc, float rad) :SphereColider(loc, rad) {
	Score = 0;
	Life = 5;

	//image‰Šú‰»
	//speed‰Šú‰»
}

void Player::Update() {
	Location l;
	l.X = GetLocation().X + 0.1f;
	l.Y = GetLocation().Y;
	SetLocation(l);
}

void Player::Draw() {
	DrawCircle(GetLocation().X, GetLocation().Y, GetRadius(), 0x0000ff);
}

void Player::Hit() {}

bool Player::LifeCheck() {
	bool ret = (Life <= 0);
	return ret;
}

int Player::GetScore() { return Score; }