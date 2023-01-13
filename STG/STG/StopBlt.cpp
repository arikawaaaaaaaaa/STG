#include "StopBlt.h"
#include"DxLib.h"
#include"common.h"

#include<math.h>

StopBlt::StopBlt(Location loc, int Stspd, float Stang, int stop, int time, int Reang,int Respd) :BulletsBase(loc, 5.f, 1, Location{ 0,0 }) {
	image = 0;

	this->time = 0;
	StopTime = stop;
	WaitTime = StopTime + time;

	Stang += 90;
	this->Reang = Reang + 90;
	float angle = (PI / 180) * Stang;
	speed.X = (cos(angle) == 0) ? 0 : cos(angle) * Stspd;	//�p�x��90��270����0���Z���Ă��܂�
	speed.Y = sin(angle) * Stspd;

	StSpd.X = speed.X;
	StSpd.Y = speed.Y;
	
	this->Respd = Respd;
}

void StopBlt::Update() {
	Location NewLoc = GetLocation();
	NewLoc.X -= speed.X;
	NewLoc.Y -= speed.Y;

	//�~�܂�܂Ō���
	if (time < StopTime) {
		speed.X -= StSpd.X / StopTime;
		speed.Y -= StSpd.Y / StopTime;
	}

	//StopTime�ȏ�̎��Ԃ��o���Ă���time�ȏ�̎��ԑҋ@���ĂȂ��Ȃ�~�܂�
	if (StopTime < time && time < WaitTime) {
		speed.X = 0;
		speed.Y = 0;
	}
	else if (time == WaitTime) {	//time�ȏ�̎��ԑҋ@��������Reang�����Ƃɑ��x��ݒ肷��
		float angle = (PI / 180) * Reang;
		speed.X = (cos(angle) == 0) ? 0 : cos(angle) * Respd;	//�p�x��90��270����0���Z���Ă��܂�
		speed.Y = sin(angle) * Respd;
	}

	SetLocation(NewLoc);
	time++;
}

void StopBlt::Draw() {
	int size = 3;
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, 5.f, 0xff00cc, true);
	//DrawBox((int)GetLocation().X - size, (int)GetLocation().Y - size, (int)GetLocation().X + size, (int)GetLocation().Y + size, 0xff00cc, TRUE);
}

bool StopBlt::isDeath() {
	float x = GetLocation().X + GetRadius();
	float y = GetLocation().Y + GetRadius();

	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;

	int margin = 255;
	if (y < 0 - margin || y > height + margin || x < 0 - margin || x > width + margin) {
		return true;
	}
	return false;
}