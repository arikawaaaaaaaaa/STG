#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "KeyMng.h"
#include"common.h"

#include<math.h>

#define AttackTime 10

Enemy::Enemy (Location loc, float rad) : SphereColider(loc, rad) {
	point = 10;
	hp = 10;
	maxhp = hp;

	Time = 0;

	//point初期化
	//hp初期化

	speed = Location{ 0,0.3 };

	bullets = new BulletsBase* [BltLimit];
	for (int i = 0; i < BltLimit; i++) {
		bullets[i] = nullptr;
	}
}

void Enemy::Update() {
	Location NewLoc = GetLocation();
	NewLoc.Y += speed.Y;
	SetLocation(NewLoc);

	Time++;

	int bulletcount;
	for (bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr) break; 

		bullets[bulletcount]->Update();

		if (bullets[bulletcount]->isDeath()) {	//弾が画面外に出た？

			DeleteBullet(bulletcount);
			bulletcount--;
		}
	}

	if (bullets[bulletcount] == nullptr && bulletcount < BltLimit && Time % AttackTime == 0) {	//画面上の弾の数は最大値未満？
		SircleShot(8, 5, GetRand(360));
		Time = 0;
	}
}

void Enemy::Draw() {
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

	DrawCircle(X, Y, Rad, 0x00ff00);

	for (int i = 0; i < BltLimit; i++) {
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}
}

void Enemy::Hit(int damage) {

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

void Enemy::DeleteBullet(int BulletCnt) {

	delete bullets[BulletCnt];
	bullets[BulletCnt] = nullptr;

	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//弾の配列にできた空白を埋める

		if (bullets[i] == nullptr) { break; }

		bullets[i - 1] = bullets[i];
		bullets[i] = nullptr;
	}
}

void Enemy::SircleShot(int way, int spd, int ang) {
	int shot = 0;

	for (int bulletcount = 0; bulletcount < BltLimit || shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new straightBlt(GetLocation(), 5, ang);	//弾を発射する
			Time = 0;
			shot++;
			ang += (360 / way);
		}
	}

}