#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "reflecBlt.h"
#include "StopBlt.h"
#include "bigBlt.h"
#include "KeyMng.h"
#include"common.h"

#include<math.h>

void Enemy::inputCSV() {
	FILE* fp; //FILE�^�\����
	errno_t error;
	switch (Stage)
	{
	case 1:
		switch (phase)
		{
		case 0:
			error = fopen_s(&fp, "data/moveinfo.csv", "r");
			break;

		case 1:
			error = fopen_s(&fp, "data/moveinfo_b.csv", "r");
			break;

		case 2:
			error = fopen_s(&fp, "data/moveinfo_c.csv", "r");
			break;

		default:
			error = fopen_s(&fp, "data/moveinfo.csv", "r");
			break;
		}
		break;

	case 2:
		switch (phase)
		{
		case 0:
			error = fopen_s(&fp, "data/moveinfo_d.csv", "r");
			break;

		case 1:
			error = fopen_s(&fp, "data/moveinfo_e.csv", "r");
			break;

		case 2:
			error = fopen_s(&fp, "data/moveinfo_f.csv", "r");
			break;

		default:
			error = fopen_s(&fp, "data/moveinfo.csv", "r");
			break;
		}
		break;

	default:
		error = fopen_s(&fp, "data/moveinfo.csv", "r");
		break;
	}

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

Enemy::Enemy(Location loc, float rad, int stage) : SphereColider(loc, rad) {

	point = 10;
	hp = hparray[(stage - 1) * 3];
	maxhp = hp;

	Stage = stage;

	shotnum = 0;

	phase = 0;

	PlayerX = 0;
	PlayerY = 0;

	Time = 0;
	angle = 0;

	LoadDivGraph("images/enemy_a.png", 4, 4, 1, 64, 64, image);

	LoadDivGraph("images/bullet_a.png", 8, 8, 1, 16, 16, bullet_A);
	LoadDivGraph("images/bullet_b.png", 8, 8, 1, 16, 16, bullet_B);
	LoadDivGraph("images/bullet_c.png", 8, 8, 1, 14, 16, bullet_C);
	LoadDivGraph("images/bullet_d.png", 8, 4, 2, 62, 62, bullet_D);

	//point������
	//hp������

	speed = Location{ 3,3 };
	Old = GetLocation();

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

	//�O�t���[���̍��W���L�^
	Old = GetLocation();

	//�ړ�
	switch (moveinfo[current].pattern) {
	case 0:		//�ړ�
		Move();
		break;

	case 1:		//�ҋ@
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

		//�G�̎�ނɂ���čU����ς���
		switch (Stage)
		{
		case 1:
			switch (phase)
			{
			case 0://1�i�K
				if (moveinfo[current].attack == 1) {
					AttackTime = 20;
					angle = Time;
					if (Time % AttackTime == 0) {
						//12�����ɍU��
						CircleShot(GetLocation(), 12, 3, angle - (Time / AttackTime), 2);
					}
				}


				if (moveinfo[current].attack == 2) {
					AttackTime = 20;
					angle = Time;
					if (Time % AttackTime == 0) {
						//12�����ɍU��
						CircleShot(GetLocation(), 12, 3, -angle - (Time / AttackTime), 2);
					}
				}
				break;

			case 1://2�i�K
					//������Ɖ������ɖ����̒e
				if (moveinfo[current].attack == 1) {
					int Xloc = 100;
					CreateShot({ GetLocation().X + GetRand(Xloc * 2) - Xloc,GetLocation().Y + GetRand(Xloc * 2) - Xloc },
						GetRand(3) + 1 + Time / 15, 0, 1);
					CreateShot({ GetLocation().X + GetRand(Xloc * 2) - Xloc,GetLocation().Y + GetRand(Xloc * 2) - Xloc },
						GetRand(3) + 1 + Time / 15, 180, 1);
				}
				break;

			case 2://3�i�K
				//���˂����e�ƎD�e
				if (moveinfo[current].attack == 1) {
					AttackTime = 90;
					if (Time % AttackTime == 1) angle = GetRand(360 - 1);
					if (Time % AttackTime >= 40) {
						if (Time % AttackTime == 40) {
							BigShot(GetLocation(), 2, angle, true, true, true, true, 0);
							BigShot(GetLocation(), 2, angle + 60, true, true, true, true, 0);
							BigShot(GetLocation(), 2, angle + 120, true, true, true, true, 0);
							BigShot(GetLocation(), 2, angle + 180, true, true, true, true, 0);
							BigShot(GetLocation(), 2, angle - 60, true, true, true, true, 0);
							BigShot(GetLocation(), 2, angle - 120, true, true, true, true, 0);
						}
						else if ((Time % AttackTime) % 10 == 0) {
							CirclerefShot(GetLocation(), 6, 2, angle, true, true, true, true, 0);
						}
					}
				}
				break;
			}
			break;

		case 2:
			switch (phase)
			{
			case 0://1�i�K
				//�����̒e���΂�܂�
				if (moveinfo[current].attack == 1) {
					AttackTime = 1;
					angle = Time;
					if (Time % AttackTime == 0) {
						CreateShot(GetLocation(), GetRand(3) + 1, GetRand(360 - 1), GetRand(7));
					}
				}
				break;

			case 1://2�i�K
				//8�����ɑ�e
				if (moveinfo[current].attack == 1) {
					if (Time == 0) {
						angle = GetRand(360 - 1);
						BigShot(GetLocation(), 2, angle, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 45, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 90, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 135, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 180, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle - 45, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle - 90, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle - 135, false, false, false, false, 0);
					}
				}

				//���@�_����3way�e
				if (moveinfo[current].attack == 2) {
					HomingShot(GetLocation(), 8, 0, 4);
					HomingShot(GetLocation(), 7, -10, 4);
					HomingShot(GetLocation(), 7, 10, 4);
				}
				break;

			case 2://3�i�K
				if (moveinfo[current].attack == 1) {
					//8�����ɒe�����������
					if (Time % 2)CircleShot(GetLocation(), 8, 5, Time / 4, 0);

					//10�����ɑ�e�����
					if (Time % 60 == 0) {
						angle = GetRand(360 - 1);
						BigShot(GetLocation(), 2, angle, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 36, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 72, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 108, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 144, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle + 180, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle - 36, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle - 72, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle - 108, false, false, false, false, 0);
						BigShot(GetLocation(), 2, angle - 144, false, false, false, false, 0);
						hp -= 1;
					}
				}

				break;
			}
			break;

		default:
			break;
		}
	}

	//�e�Ǘ�
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

	//�G�{��
	int ind = (Stage - 1) * 2;
	if (Old.X < X)		DrawRotaGraph(X, Y, 1, 0, image[ind + 1], true, true, false);
	else if (X < Old.X) DrawRotaGraph(X, Y, 1, 0, image[ind + 1], true, false, false);
	else				DrawRotaGraph(X, Y, 1, 0, image[ind], true, false, false);

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

	//�i�s�����ȉ��Ȃ�i�s�x�𑝂₷
	if (let && phase < 2) {
		phase++;
		maxhp = hparray[(Stage - 1) * 3 + phase];	//�̗̓��Z�b�g
		hp = maxhp;
		inputCSV();		//�U���p�^�[�����Z�b�g
		waittime = 0;
		Time = 0;
		current = 0;
		return false;
	}
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

void Enemy::CircleShot(Location loc, int way, float spd, float ang, int col) {		//�~�`�V���b�g(way���A�e���A�p�x�A�F)
	int shot = 0;	//�e�𔭎˂�����

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new straightBlt(loc, spd, ang, col, bullet_A);	//�e�𔭎˂���

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

void Enemy::CreateShot(Location loc, float spd, float angle, int col)
{
	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new straightBlt(loc, spd, angle, col, bullet_A);	//�e�𔭎˂���
			break;
		}

	}
}

void Enemy::BigShot(Location loc, int spd, float ang, bool up, bool right, bool down, bool left, int col) {		//�~�`�V���b�g(way���A�e���A�p�x�A�e�����̕ǂŔ��˂��邩(���ꂼ���A�E�A���A������)�A�F)
	int shot = 0;	//�e�𔭎˂�����

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new bigBlt(loc, spd, ang, 1, up, right, down, left, col, bullet_D);	//�e�𔭎˂���
			break;
		}

	}

}

void Enemy::CirclerefShot(Location loc, int way, int spd, float ang, bool up, bool right, bool down, bool left, int col) {		//�~�`�V���b�g(way���A�e���A�p�x�A�e�����̕ǂŔ��˂��邩(���ꂼ���A�E�A���A������)�A�F)
	int shot = 0;	//�e�𔭎˂�����

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new reflecBlt(loc, spd, ang, 1, up, right, down, left, col, bullet_C);	//�e�𔭎˂���

			shot++;				//���˂������𑝂₷
			ang += (360.f / way);	//�p�x�𒲐�����
		}

	}

}

void Enemy::HomingShot(Location loc, float spd, int ang, int col) {		//���@�_��(�e���A���炵�A�F)

	//�v���C���[�Ԃ̊p�x�擾------
	double tan = atan2(((double)PlayerY - loc.Y),
		(double)PlayerX - loc.X);

	int angle = (int)(tan * 180 / PI) + 90;
	//----------------------------

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new straightBlt(loc, spd, angle + ang, col, bullet_A);	//�e�𔭎˂���
			break;
		}
	}
}

void Enemy::StopShot(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd, int col) {

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new StopBlt(loc, Stspd, Stang, stop, time, Reang, Respd, col, bullet_B);	//�e�𔭎˂���
			break;
		}
	}
}

//��x�~�܂�~�`�V���b�g(�e���Away���A�F�A���߂̑��x�A�~�܂�܂ł̎��ԁA�ҋ@���ԁA���̑��x�A���̒e���AReang��way���ɉ����ĕω������邩)
void Enemy::CircleStopShot(Location loc, int way, int Stspd, float Stang, int stop, int time, int Reang, int Respd, bool ChangeReang, int col) {
	int shot = 0;	//�e�𔭎˂�����

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new StopBlt(loc, Stspd, Stang, stop, time, Reang, Respd, col, bullet_B);	//�e�𔭎˂���

			shot++;				//���˂������𑝂₷
			Stang += (360.f / way);	//�p�x�𒲐�����
			if (ChangeReang)Reang += (360.f / way);
		}

	}

}