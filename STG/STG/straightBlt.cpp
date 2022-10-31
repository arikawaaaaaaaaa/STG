#include "straightBlt.h"
#include"DxLib.h"

straightBlt::straightBlt(Location loc) :BulletsBase(loc, 5.f, 1, Location{ 0,5 }) {
	image = 0;
}

void straightBlt::Update(){
	Location NewLoc = GetLocation();
	NewLoc.Y -= speed.Y;
	SetLocation(NewLoc);

}

void straightBlt::Draw() {
	DrawBox((int)GetLocation().X - 2, (int)GetLocation().Y - 4, (int)GetLocation().X + 2, (int)GetLocation().Y + 4, 0xff00cc, TRUE);
}

bool straightBlt::isDeath() {
	float y = GetLocation().Y + GetRadius();

	if (y <= 0) {
		return true;
	}
	return false;
}
