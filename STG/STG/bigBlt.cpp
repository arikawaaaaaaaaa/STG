#include "bigBlt.h"
#include"DxLib.h"
#include"common.h"

#include<math.h>

bigBlt::bigBlt(Location loc, float spd, float ang, int ref, bool up, bool right, bool down, bool left, int col, int img[8]) :BulletsBase(loc, 16.f, 1, Location{ 0,0 }) {

	for (int i = 0; i < 8; i++)
	{
		image[i] = img[i];
	}
	color = col;

	DrawAng = (PI / 180) * ang;
	Refcnt = ref;

	ang += 90;
	float angle = (PI / 180) * ang;
	speed.X = (cos(angle) == 0) ? 0 : cos(angle) * spd;	//Šp“x‚ª90‚©270‚¾‚Æ0™ŽZ‚µ‚Ä‚µ‚Ü‚¤
	speed.Y = sin(angle) * spd;

	wall.UP = up;
	wall.RIGHT = right;
	wall.DOWN = down;
	wall.LEFT = left;
}

void bigBlt::Update() {
	Location NewLoc = GetLocation();
	NewLoc.X -= speed.X;
	NewLoc.Y -= speed.Y;

	if (Refcnt > 0) {
		if (NewLoc.Y <= 0 && wall.UP) {
			speed.Y *= -1;
			Refcnt--;
		}
		if (NewLoc.X >= SCREEN_WIDTH - SCREEN_MARGIN && wall.RIGHT) {
			speed.X *= -1;
			Refcnt--;
		}
		if (NewLoc.Y >= SCREEN_HEIGHT && wall.DOWN) {
			speed.Y *= -1;
			Refcnt--;
		}
		if (NewLoc.X <= SCREEN_MARGIN && wall.LEFT) {
			speed.X *= -1;
			Refcnt--;
		}
	}
	SetLocation(NewLoc);
	DrawAng++;
}

void bigBlt::Draw() {
	int size = 3;
	DrawRotaGraph((int)GetLocation().X, (int)GetLocation().Y, 1, DrawAng, image[color], true, false);
	//DrawCircle((int)GetLocation().X, (int)GetLocation().Y, GetRadius(), 0xff0000, TRUE);
}

bool bigBlt::isDeath() {
	float x = GetLocation().X + GetRadius();
	float y = GetLocation().Y + GetRadius();

	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;

	int margin = 124;
	if (y < 0 - margin || y > height + margin || x < 0 || x > width) {
		return true;
	}
	return false;
}
