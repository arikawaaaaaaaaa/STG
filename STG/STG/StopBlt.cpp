#include "StopBlt.h"
#include"DxLib.h"
#include"common.h"

#include<math.h>

StopBlt::StopBlt(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd, int col, int img[8]) :BulletsBase(loc, 5.f, 1, Location{ 0,0 }) {

	for (int i = 0; i < 8; i++)
	{
		image[i] = img[i];
	}
	color = col;

	DrawAng = (PI / 180) * Stang;

	this->time = 0;
	StopTime = stop;
	WaitTime = StopTime + time;

	Stang += 90;
	this->Reang = Reang + 90;
	float angle = (PI / 180) * Stang;
	speed.X = (cos(angle) == 0) ? 0 : cos(angle) * Stspd;	//Šp“x‚ª90‚©270‚¾‚Æ0™ŽZ‚µ‚Ä‚µ‚Ü‚¤
	speed.Y = sin(angle) * Stspd;

	StSpd.X = speed.X;
	StSpd.Y = speed.Y;
	
	this->Respd = Respd;
}

void StopBlt::Update() {
	Location NewLoc = GetLocation();
	NewLoc.X -= speed.X;
	NewLoc.Y -= speed.Y;

	//Ž~‚Ü‚é‚Ü‚ÅŒ¸‘¬
	if (time < StopTime) {
		speed.X -= StSpd.X / StopTime;
		speed.Y -= StSpd.Y / StopTime;
	}

	//StopTimeˆÈã‚ÌŽžŠÔ‚ªŒo‚Á‚Ä‚¢‚ÄtimeˆÈã‚ÌŽžŠÔ‘Ò‹@‚µ‚Ä‚È‚¢‚È‚çŽ~‚Ü‚é
	if (StopTime < time && time < WaitTime) {
		speed.X = 0;
		speed.Y = 0;
	}
	else if (time == WaitTime) {	//timeˆÈã‚ÌŽžŠÔ‘Ò‹@‚µ‚½Žž‚ÉReang‚ð‚à‚Æ‚É‘¬“x‚ðÝ’è‚·‚é
		DrawAng = (PI / 180) * Reang;
		float angle = (PI / 180) * Reang;
		speed.X = (cos(angle) == 0) ? 0 : cos(angle) * Respd;	//Šp“x‚ª90‚©270‚¾‚Æ0™ŽZ‚µ‚Ä‚µ‚Ü‚¤
		speed.Y = sin(angle) * Respd;
	}

	SetLocation(NewLoc);
	time++;
}

void StopBlt::Draw() {
	int size = 3;
	DrawRotaGraph((int)GetLocation().X, (int)GetLocation().Y, 1, DrawAng, image[color], true, false);
	//DrawBox((int)GetLocation().X - size, (int)GetLocation().Y - size, (int)GetLocation().X + size, (int)GetLocation().Y + size, 0xff00cc, TRUE);
}

bool StopBlt::isDeath() {
	float x = GetLocation().X + GetRadius();
	float y = GetLocation().Y + GetRadius();

	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;

	int margin = 255;
	if (y < 0 - margin || y > height + margin || x < 0 || x > width) {
		return true;
	}
	return false;
}