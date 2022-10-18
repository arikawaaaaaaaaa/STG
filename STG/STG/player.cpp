#include"player.h"
#include"dxlib.h"
#include"KeyMng.h"
#include"straightBlt.h"

Location GetNewLocation(Location NewLoc);

Player::Player(Location loc, float rad) :SphereColider(loc, rad) {
	Score = 0;
	Life = 5;

	//image‰Šú‰»
	//speed‰Šú‰»

	bullets = new BulletsBase*[30];
	for (int i = 0; i < 30; i++) {
		bullets[i] = nullptr;
	}
}

void Player::Update() {

	Location NewLoc = GetNewLocation(GetLocation());
	SetLocation(NewLoc);

	int bulletcount;
	for (bulletcount = 0; bulletcount < 30; bulletcount++) {
		if (bullets[bulletcount] == nullptr) { break; }
		bullets[bulletcount]->Update();
	}

	if (KeyMng::OnClick(KEY_INPUT_Z)) {
		int i;
		int cap = 30;
		for (i = 0; i < cap; i++) {
			if (bullets[i] == nullptr) { break; }
		}
		if (i < cap) bullets[i] = new straightBlt(GetLocation());
	}
}

void Player::Draw() {
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, (int)GetRadius(), 0xff0000);

	for (int i = 0; i < 30; i++) {
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}
}

void Player::Hit() {}

bool Player::LifeCheck() {
	bool ret = (Life <= 0);
	return ret;
}

int Player::GetScore() { return Score; }

Location GetNewLocation(Location NewLoc) {
	
	if (KeyMng::OnPress(KEY_INPUT_RIGHT)) {
		NewLoc.X += 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X -= 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_LEFT)) {
		NewLoc.X -= 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X += 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_UP)) {
		NewLoc.Y -= 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y += 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_DOWN)) {
		NewLoc.Y += 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y -= 1.5f;
	}

	if (NewLoc.X < 0)NewLoc.X = 0.0;
	if (NewLoc.Y < 0)NewLoc.Y = 0.0;
	if (NewLoc.X > 1280)NewLoc.X = 1280.0;
	if (NewLoc.Y > 720)NewLoc.Y = 720.0;

	return NewLoc;
}