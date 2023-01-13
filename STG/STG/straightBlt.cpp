#include "straightBlt.h"
#include"DxLib.h"
#include"common.h"

#include<math.h>

straightBlt::straightBlt(Location loc, float spd, float ang) :BulletsBase(loc, 5.f, 1, Location{ 0,0 }) {
	image = 0;

	ang += 90;
	float angle = (PI / 180) * ang;
	speed.X = (cos(angle) == 0) ? 0 : cos(angle) * spd;	//äpìxÇ™90Ç©270ÇæÇ∆0èôéZÇµÇƒÇµÇ‹Ç§
	speed.Y = sin(angle) * spd;
}

void straightBlt::Update(){
	Location NewLoc = GetLocation();
	NewLoc.X -= speed.X;
	NewLoc.Y -= speed.Y;
	SetLocation(NewLoc);

}

void straightBlt::Draw() {
	int size = 3;
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, 5.f, 0xff00cc, true);
	//DrawBox((int)GetLocation().X - size, (int)GetLocation().Y - size, (int)GetLocation().X + size, (int)GetLocation().Y + size, 0xff00cc, TRUE);
}

bool straightBlt::isDeath() {
	float x = GetLocation().X + GetRadius();
	float y = GetLocation().Y + GetRadius();

	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;

	int margin = 20;
	if (y < 0 - margin || y > height + margin || x < 0 - margin || x > width + margin) {
		return true;
	}
	return false;
}
