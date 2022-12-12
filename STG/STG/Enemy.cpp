#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "reflecBlt.h"
#include "KeyMng.h"
#include"common.h"

#include<math.h>

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

	speed = Location{ 0,0.3 };

	bullets = new BulletsBase* [BltLimit];
	for (int i = 0; i < BltLimit; i++) {
		bullets[i] = nullptr;
	}
}

void Enemy::Update() {
	Location NewLoc = GetLocation();
	//NewLoc.Y += speed.Y;
	SetLocation(NewLoc);

	Time++;

	int bulletcount;
	for (bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr) break; 

		bullets[bulletcount]->Update();

		if (bullets[bulletcount]->isDeath()) {	//弾が画面外に出た？

			DeleteBullet(bulletcount);	//弾を消す
			bulletcount--;
		}
	}

	int AttackTime = 0;	//攻撃間隔
	if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {	//画面上の弾の数は最大値未満？
		switch (hp)
		{
		case 10:
			AttackTime = 10;
			if (Time % AttackTime == 0) SircleShot(GetLocation(), 8, 3, GetRand(360), false);
			break;

		case 9:
			AttackTime = 5;
			if (Time % AttackTime == 0) HomingShot(GetLocation(), 3);
			break;

		case 8:
			AttackTime = 120;
			if (Time % AttackTime == 0) SircleShot({ GetRand(160) + GetLocation().X - 80,GetRand(160) + GetLocation().Y - 80 }, 36, 2, GetRand(360), true);
			break;

		case 7:
			AttackTime = 3;
			if (Time % AttackTime == 0) SircleShot(GetLocation(), 3, 6, shotnum, false);
			if (Time % 600 < 300)shotnum += Time % 300 / 4;
			else shotnum -= (300 - Time % 300) / 4;
			break;

		default:
			break;
		}
	}
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

void Enemy::SircleShot(Location loc, int way, int spd, float ang, bool ref) {		//円形ショット(way数、弾速、角度、反射するか)
	int shot = 0;	//弾を発射した数

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			if (!ref)bullets[bulletcount] = new straightBlt(loc, spd, ang);	//弾を発射する
			else bullets[bulletcount] = new reflecBlt(loc, spd, ang, 1);	//弾を発射する

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