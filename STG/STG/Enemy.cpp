#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "reflecBlt.h"
#include "StopBlt.h"
#include "KeyMng.h"
#include"common.h"

#include<math.h>

//�}�b�v�[ X 1280 Y 720
//
//Moveinfo moveinfo[] = {
//	{0, 640,150,1,  0,0},
//	{0, 490,200,2,  0,2},
//	{1,   0,  0,3,180,1},
//	{0, 640,250,4,  0,2},
//	{1,   0,  0,5,180,1},
//	{0, 740,200,6,  0,2},
//	{1,   0,  0,7,180,1},
//	{0, 640,150,8,  0,2},
//	{1,   0,  0,1,180,1},
//};


//Location locations[3] = {
//	{640,150},
//	{1200,150},
//	{80,150},
//};

void Enemy::inputCSV() {
	FILE* fp; //FILE�^�\����
	errno_t error;
	error = fopen_s(&fp, "data/moveinfo.csv", "r");

	if (error != 0) {
		//�t�@�C�����J���Ă��Ȃ�
		return;
	}
	else {
		//�t�@�C�����J����
		char line[100];
		for (int i = 0; fgets(line, 100, fp) != NULL; i++) {
			sscanf_s(line, "%d,%f,%f,%f,%f,%d,%d,%d",
				&moveinfo[i].pattern,
				&moveinfo[i].Point.X,
				&moveinfo[i].Point.Y,
				&moveinfo[i].Speed.X,
				&moveinfo[i].Speed.Y,
				&moveinfo[i].nextPointnum,
				&moveinfo[i].Waittime,
				&moveinfo[i].attack
				);
		}
		return;
	}

	fclose(fp);	//�t�@�C�������
}

Enemy::Enemy (Location loc, float rad) : SphereColider(loc, rad) {

	point = 10;
	hp = 100;
	maxhp = hp;

	shotnum = 0;

	PlayerX = 0;
	PlayerY = 0;

	Time = 0;

	//point������
	//hp������

	speed = Location{ 3,3 };

	bullets = new BulletsBase* [BltLimit];
	for (int i = 0; i < BltLimit; i++) {
		bullets[i] = nullptr;
	}

	//�U���p�^�[���ǂݍ���
	inputCSV();

	current = 0;
	waittime = 0;
}

void Enemy::Update() {
	//Location NewLoc = GetLocation();
	////NewLoc.Y += speed.Y;
	//SetLocation(NewLoc);

	//Move();

	switch (moveinfo[current].pattern) {
	case 0:
		Move();
		break;

	case 1:
		waittime++;

		if (moveinfo[current].Waittime <= waittime) {
			waittime = 0;
			current = moveinfo[current].nextPointnum;
			Time = 0;
		}
		break;
	}

	int AttackTime = 0;	//�U���Ԋu
	if (moveinfo[current].attack != 0) {
		if (moveinfo[current].attack == 1) {
			AttackTime = 30;
			int angle = Time;
			if (Time % AttackTime == 0) {

				//SircleStopShot(GetLocation(), 80, 5, angle, 30, 30, angle+180, 2, true);
				SirclerefShot(GetLocation(), 8, 2, angle + (3*Time / AttackTime), true, true, true, true, 1);

			}
		}


		if (moveinfo[current].attack == 2) {
			AttackTime = 20;
			int angle = Time;
			if (Time % AttackTime == 0) {

				//SircleStopShot(GetLocation(), 80, 5, angle, 30, 30, angle+180, 2, true);
				SircleStopShot(GetLocation(), 12, 4, angle + (Time / AttackTime), 30, 30, angle + (Time / AttackTime) + 180, 3, true, 2);

			}
		}
	}


	int bulletcount;
	for (bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr) break; 

		bullets[bulletcount]->Update();

		if (bullets[bulletcount]->isDeath()) {	//�e����ʊO�ɏo���H

			DeleteBullet(bulletcount);	//�e������
			bulletcount--;
		}
	}

	Time++;


	//if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {	//��ʏ�̒e�̐��͍ő�l�����H
	//	switch (hp)
	//	{
	//	case 10:
	//		AttackTime = 10;
	//		if (Time % AttackTime == 0) SircleShot(GetLocation(), 8, 3, GetRand(360));
	//		break;

	//	case 9:
	//		AttackTime = 5;
	//		if (Time % AttackTime == 0) HomingShot(GetLocation(), 3);
	//		break;

	//	case 8:
	//		AttackTime = 120;
	//		if (Time % AttackTime == 0) SirclerefShot({ GetRand(160) + GetLocation().X - 80,GetRand(160) + GetLocation().Y - 80 }, 36, 2, GetRand(360), true, true, false, true);
	//		break;

	//	case 7:
	//		AttackTime = 3;
	//		if (Time % AttackTime == 0) SircleShot(GetLocation(), 6, 2, shotnum);
	//		if (Time % 600 < 300)shotnum += Time % 300 / 8;
	//		else shotnum -= (300 - Time % 300) / 8;
	//		break;

	//	default:
	//		break;
	//	}
	//}
}

void Enemy::Draw() {	//�`��
	int X = (int)GetLocation().X;
	int Y = (int)GetLocation().Y;
	int Rad = (int)GetRadius();

	float size = 30;

	//�̗̓o�[

	//�Ԃ��Ƃ�
	DrawBox(X - size, Y - Rad - 10,
			X + size, Y - Rad - 15, 0xff0000, TRUE);

	//�΂̂Ƃ�
	DrawBox(X - size, Y - Rad - 10,
			(X - size) + size * 2 * ((float)hp / maxhp), Y - Rad - 15, 0x00ff00, TRUE);

	DrawCircle(X, Y, Rad, 0x00ff00);	//�G�{��

	for (int i = 0; i < BltLimit; i++) {	//�e
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}
}

void Enemy::Hit(int damage) {	//��e��

	if (damage >= 0) {
		hp -= damage;
		if (hp < 0) hp = 0;
	}

}

//void Enemy::HitPlayer(int BulletCnt) {
//
//	delete bullets[BulletCnt];
//	bullets[BulletCnt] = nullptr;
//
//	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//�e�̔z��ɂł����󔒂𖄂߂�
//
//		if (bullets[i] == nullptr) { break; }
//
//		bullets[i - 1] = bullets[i];
//		bullets[i] = nullptr;
//	}
//}

void Enemy::Hit() {}

bool Enemy::Checkhp() { 
	bool let = (hp <= 0);
	return let;
}

int Enemy::Getpoint() { return point; }

void Enemy::DeleteBullet(int BulletCnt) {		//�e������

	delete bullets[BulletCnt];
	bullets[BulletCnt] = nullptr;

	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//�e�̔z��ɂł����󔒂𖄂߂�

		if (bullets[i] == nullptr) { break; }

		bullets[i - 1] = bullets[i];
		bullets[i] = nullptr;
	}
}

void Enemy::GetPlayerStat(Player* player) {		//�v���C���[�̍��W���擾

	PlayerX = player->GetLocation().X;
	PlayerY = player->GetLocation().Y;
}

void Enemy::SircleShot(Location loc, int way, int spd, float ang, int col) {		//�~�`�V���b�g(way���A�e���A�p�x�A�F)
	int shot = 0;	//�e�𔭎˂�����

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new straightBlt(loc, spd, ang, col);	//�e�𔭎˂���

			shot++;				//���˂������𑝂₷
			ang += (360.f / way);	//�p�x�𒲐�����
		}

	}

}

void Enemy::Move() {
	float angle = 0;

	Location NewLoc = GetLocation();

	//�ړI�n�ɒ�������I��
	if ((NewLoc.X == moveinfo[current].Point.X) &&
		(NewLoc.Y == moveinfo[current].Point.Y)) {
		current = moveinfo[current].nextPointnum;
		Time = 0;
		return;
	}
	else {

		double tan = atan2((double)moveinfo[current].Point.Y - NewLoc.Y,
						   (double)moveinfo[current].Point.X - NewLoc.X);

		int angbase = (int)(tan * 180 / PI);
		float ang = (PI / 180) * angbase;

		speed.X = moveinfo[current].Speed.X;
		speed.Y = moveinfo[current].Speed.Y;

		if (NewLoc.X != moveinfo[current].Point.X) {

			float speedX = (cos(angbase) == 0) ? 0 : cos(ang) * speed.X;	//�p�x��90��270����0���Z���Ă��܂�

			if (NewLoc.X < moveinfo[current].Point.X) {
				NewLoc.X += speedX;
				if (moveinfo[current].Point.X < NewLoc.X) NewLoc.X = moveinfo[current].Point.X;
			}
			else if (moveinfo[current].Point.X < NewLoc.X ) {
				NewLoc.X += speedX;
				if (NewLoc.X < moveinfo[current].Point.X) NewLoc.X = moveinfo[current].Point.X;
			}
		}

		if (NewLoc.Y != moveinfo[current].Point.Y) {

			float speedY = sin(ang) * speed.Y;

			if (NewLoc.Y < moveinfo[current].Point.Y) {
				NewLoc.Y += speedY;
				if (moveinfo[current].Point.Y < NewLoc.Y) NewLoc.Y = moveinfo[current].Point.Y;
			}
			else if (moveinfo[current].Point.Y < NewLoc.Y) {
				NewLoc.Y += speedY;
				if (NewLoc.Y < moveinfo[current].Point.Y) NewLoc.Y = moveinfo[current].Point.Y;
			}
		}
	}

	SetLocation(NewLoc);
	
}

void Enemy::SirclerefShot(Location loc, int way, int spd, float ang, bool up, bool right, bool down, bool left, int col) {		//�~�`�V���b�g(way���A�e���A�p�x�A�e�����̕ǂŔ��˂��邩(���ꂼ���A�E�A���A������)�A�F)
	int shot = 0;	//�e�𔭎˂�����

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new reflecBlt(loc, spd, ang, 1, up, right, down, left, col);	//�e�𔭎˂���

			shot++;				//���˂������𑝂₷
			ang += (360.f / way);	//�p�x�𒲐�����
		}

	}

}

void Enemy::HomingShot(Location loc, int spd, int col) {		//���@�_��(�e���A�F)

	//�v���C���[�Ԃ̊p�x�擾------
	double tan = atan2(((double)PlayerY - loc.Y),
		(double)PlayerX - loc.X);

	int ang = (int)(tan * 180 / PI) + 90;
	//----------------------------

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new straightBlt(loc, spd, ang, col);	//�e�𔭎˂���
			break;
		}
	}
}

void Enemy::StopShot(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd, int col) {

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new StopBlt(loc, Stspd, Stang, stop, time, Reang, Respd, col);	//�e�𔭎˂���
			break;
		}
	}
}

//��x�~�܂�~�`�V���b�g(�e���Away���A�F�A���߂̑��x�A�~�܂�܂ł̎��ԁA�ҋ@���ԁA���̑��x�A���̒e���AReang��way���ɉ����ĕω������邩)
void Enemy::SircleStopShot(Location loc, int way, int Stspd, float Stang, int stop, int time, int Reang, int Respd, bool ChangeReang, int col) {
	int shot = 0;	//�e�𔭎˂�����

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new StopBlt(loc, Stspd, Stang, stop, time, Reang, Respd, col);	//�e�𔭎˂���

			shot++;				//���˂������𑝂₷
			Stang += (360.f / way);	//�p�x�𒲐�����
			if (ChangeReang)Reang += (360.f / way);
		}

	}

}