#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "reflecBlt.h"
#include "KeyMng.h"
#include"common.h"

#include<math.h>

struct Moveinfo {
	int pattern;	//行動パターン
	Location Point;	//目的地
	int nextPointnum;	//次の配列番号
	int Waittime;	//待ち時間
	int  attack;	//攻撃の種類
};

//マップ端 X 1280 Y 720

Moveinfo moveinfo[] = {
	{0, 640,150,1,  0,0},
	{0, 100,360,2,  0,2},
	{1,   0,  0,3,300,1},
	{0, 640,570,4,  0,2},
	{1,   0,  0,5,300,1},
	{0,1180,360,6,  0,2},
	{1,   0,  0,7,300,1},
	{0, 640,150,8,  0,2},
	{1,   0,  0,1,300,1},
};

//Location locations[3] = {
//	{640,150},
//	{1200,150},
//	{80,150},
//};

int next[3] = { 1,2,1 };

int current = 0;
int waittime = 0;

Enemy::Enemy (Location loc, float rad) : SphereColider(loc, rad) {
	point = 10;
	hp = 10;
	maxhp = hp;

	shotnum = 0;

	PlayerX = 0;
	PlayerY = 0;

	Time = 0;

	//point初期化
	//hp初期化

	speed = Location{ 3,3 };

	bullets = new BulletsBase* [BltLimit];
	for (int i = 0; i < BltLimit; i++) {
		bullets[i] = nullptr;
	}
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
		}
		break;
	}

	Time++;

	int AttackTime = 0;	//攻撃間隔
	if (moveinfo[current].attack != 0) {
		if (moveinfo[current].attack == 1) {
			AttackTime = 20;
			if (Time % AttackTime == 0) SircleShot(GetLocation(), 8, 3, GetRand(360));	//円形ショット
		}

		if (moveinfo[current].attack == 2) {
			AttackTime = 120;
			if (Time % AttackTime == 0) SirclerefShot({ GetRand(160) + GetLocation().X - 80,GetRand(160) + GetLocation().Y - 80 }, 36, 2, GetRand(360),
														true, true, false, true);		//反射円形ショット
		}
	}


	int bulletcount;
	for (bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr) break; 

		bullets[bulletcount]->Update();

		if (bullets[bulletcount]->isDeath()) {	//弾が画面外に出た？

			DeleteBullet(bulletcount);	//弾を消す
			bulletcount--;
		}
	}


	//if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {	//画面上の弾の数は最大値未満？
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

void Enemy::Draw() {	//描画
	int X = (int)GetLocation().X;
	int Y = (int)GetLocation().Y;
	int Rad = (int)GetRadius();

	float size = 30;

	//体力バー

	//赤いとこ
	DrawBox(X - size, Y - Rad - 10,
			X + size, Y - Rad - 15, 0xff0000, TRUE);

	//緑のとこ
	DrawBox(X - size, Y - Rad - 10,
			(X - size) + size * 2 * ((float)hp / maxhp), Y - Rad - 15, 0x00ff00, TRUE);

	DrawCircle(X, Y, Rad, 0x00ff00);	//敵本体

	for (int i = 0; i < BltLimit; i++) {	//弾
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}
}

void Enemy::Hit(int damage) {	//被弾時

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
//	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//弾の配列にできた空白を埋める
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

void Enemy::DeleteBullet(int BulletCnt) {		//弾を消す

	delete bullets[BulletCnt];
	bullets[BulletCnt] = nullptr;

	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//弾の配列にできた空白を埋める

		if (bullets[i] == nullptr) { break; }

		bullets[i - 1] = bullets[i];
		bullets[i] = nullptr;
	}
}

void Enemy::GetPlayerStat(Player* player) {		//プレイヤーの座標を取得

	PlayerX = player->GetLocation().X;
	PlayerY = player->GetLocation().Y;
}

void Enemy::SircleShot(Location loc, int way, int spd, float ang) {		//円形ショット(way数、弾速、角度)
	int shot = 0;	//弾を発射した数

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new straightBlt(loc, spd, ang);	//弾を発射する

			shot++;				//発射した数を増やす
			ang += (360.f / way);	//角度を調整する
		}

	}

}

void Enemy::Move() {
	float angle = 0;

	Location NewLoc = GetLocation();

	if ((NewLoc.X == moveinfo[current].Point.X) &&
		(NewLoc.Y == moveinfo[current].Point.Y)) {
		current = moveinfo[current].nextPointnum;
		return;
	}
	else {

		double tan = atan2((double)moveinfo[current].Point.Y - NewLoc.Y,
						   (double)moveinfo[current].Point.X - NewLoc.X);

		int angbase = (int)(tan * 180 / PI);
		float ang = (PI / 180) * angbase;

		if (NewLoc.X != moveinfo[current].Point.X) {

			float speedX = (cos(angbase) == 0) ? 0 : cos(ang) * speed.X;	//角度が90か270だと0徐算してしまう

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

void Enemy::SirclerefShot(Location loc, int way, int spd, float ang, bool up, bool right, bool down, bool left) {		//円形ショット(way数、弾速、角度、各方向の壁で反射するか(それぞれ上、右、下、左方向))
	int shot = 0;	//弾を発射した数

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			bullets[bulletcount] = new reflecBlt(loc, spd, ang, 1, up, right, down, left);	//弾を発射する

			shot++;				//発射した数を増やす
			ang += (360.f / way);	//角度を調整する
		}

	}

}

void Enemy::HomingShot(Location loc, int spd) {		//自機狙い(弾速)

	//プレイヤー間の角度取得------
	double tan = atan2(((double)PlayerY - loc.Y),
		(double)PlayerX - loc.X);

	int ang = (int)(tan * 180 / PI) + 90;
	//----------------------------

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new straightBlt(loc, spd, ang);	//弾を発射する
			break;
		}
	}
}