#include "rotaBlt.h"
#include"DxLib.h"
#include"common.h"

#include<math.h>

rotaBlt::rotaBlt(Location loc, float spd, int ang) :BulletsBase(loc, 5.f, 1, Location{ 0,0 }) {

	ang += 90;
	ang %= 360;
	float angle = (PI / 180) * ang;
	speed.X = (abs(ang) == 90 || abs(ang) == 270) ? 0 : cos(ang) * spd;	//äpìxÇ™90Ç©270ÇæÇ∆0èôéZÇµÇƒÇµÇ‹Ç§
	speed.Y = sin(angle) * spd;
}

void rotaBlt::Update() {
	Location NewLoc = GetLocation();
	NewLoc.X -= speed.X;
	NewLoc.Y -= speed.Y;
	SetLocation(NewLoc);

}

void rotaBlt::Draw() {
	int size = 3;
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, 5.f, 0xff00cc, true);
	//DrawBox((int)GetLocation().X - size, (int)GetLocation().Y - size, (int)GetLocation().X + size, (int)GetLocation().Y + size, 0xff00cc, TRUE);
}

bool rotaBlt::isDeath() {
	float x = GetLocation().X + GetRadius();
	float y = GetLocation().Y + GetRadius();

	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;

	int margin = 20;
	if (y < 0 - margin || y > height + margin || x < 0|| x > width) {
		return true;
	}
	return false;
}
