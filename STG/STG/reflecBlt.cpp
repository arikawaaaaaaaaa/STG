#include "reflecBlt.h"
#include"DxLib.h"
#include"common.h"

#include<math.h>

reflecBlt::reflecBlt(Location loc, float spd, float ang, int ref, bool up, bool right, bool down, bool left) :BulletsBase(loc, 5.f, 1, Location{ 0,0 }) {
	image = 0;
	Refcnt = ref;

	ang += 90;
	float angle = (PI / 180) * ang;
	speed.X = (cos(angle) == 0) ? 0 : cos(angle) * spd;	//Šp“x‚ª90‚©270‚¾‚Æ0™ŽZ‚µ‚Ä‚µ‚Ü‚¤
	speed.Y = sin(angle) * spd;

	wall.UP = up;
	wall.RIGHT = right;
	wall.DOWN =down;
	wall.LEFT = left;
}

void reflecBlt::Update() {
	Location NewLoc = GetLocation();
	NewLoc.X -= speed.X;
	NewLoc.Y -= speed.Y;

	if (Refcnt > 0) {
		if (NewLoc.Y <= 0 && wall.UP) {
			speed.Y *= -1;
			Refcnt--;
		}
		if (NewLoc.X >= SCREEN_WIDTH && wall.RIGHT) {
			speed.X *= -1;
			Refcnt--;
		}
		if (NewLoc.Y >= SCREEN_HEIGHT && wall.DOWN) {
			speed.Y *= -1;
			Refcnt--;
		}
		if (NewLoc.X <= 0 && wall.LEFT) {
			speed.X *= -1;
			Refcnt--;
		}
	}
	SetLocation(NewLoc);

}

void reflecBlt::Draw() {
	int size = 3;
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, 5.f, 0xff00cc, true);
	//DrawBox((int)GetLocation().X - size, (int)GetLocation().Y - size, (int)GetLocation().X + size, (int)GetLocation().Y + size, 0xff00cc, TRUE);
}

bool reflecBlt::isDeath() {
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
