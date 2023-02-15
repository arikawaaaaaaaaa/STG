#include "straightBlt.h"
#include"DxLib.h"
#include"common.h"

#include<math.h>

straightBlt::straightBlt(Location loc, float spd, float ang, int col,int img[8]) :BulletsBase(loc, 5.f, 1, Location{ 0,0 }) {

	for (int i = 0; i < 8; i++)
	{
		image[i] = img[i];
	}

	color = col;

	DrawAng = (PI / 180) * ang;

	ang += 90;
	float angle = (PI / 180) * ang;
	speed.X = (cos(angle) == 0) ? 0 : cos(angle) * spd;	//Šp“x‚ª90‚©270‚¾‚Æ0™ŽZ‚µ‚Ä‚µ‚Ü‚¤
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
	DrawRotaGraph((int)GetLocation().X, (int)GetLocation().Y, 1 , DrawAng, image[color], true, false);
	//DrawBox((int)GetLocation().X - size, (int)GetLocation().Y - size, (int)GetLocation().X + size, (int)GetLocation().Y + size, 0xff00cc, TRUE);
}

bool straightBlt::isDeath() {
	float x = GetLocation().X + GetRadius();
	float y = GetLocation().Y + GetRadius();

	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;

	int margin = 20;
	if (y < 0 - margin || y > height + margin || x < 0 || x > width) {
		return true;
	}
	return false;
}
