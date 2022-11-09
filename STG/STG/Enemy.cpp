#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "KeyMng.h"

Enemy::Enemy (Location loc, float rad) : SphereColider(loc, rad) {
	point = 10;
	hp = 10;

	Time = 0;

	//point初期化
	//hp初期化

	speed = Location{ 0,0.5 };

	bullets = new BulletsBase* [30];
	for (int i = 0; i < 30; i++) {
		bullets[i] = nullptr;
	}
}

void Enemy::Update() {
	Location NewLoc = GetLocation();
	NewLoc.Y += speed.Y;
	SetLocation(NewLoc);

	Time++;

	int bulletcount;
	for (bulletcount = 0; bulletcount < 30; bulletcount++) {

		if (bullets[bulletcount] == nullptr) break; 

		bullets[bulletcount]->Update();

		if (bullets[bulletcount]->isDeath()) {	//弾が画面外に出た？

			delete bullets[bulletcount];		//出た弾を消す
			bullets[bulletcount] = nullptr;

			for (int i = bulletcount + 1; i < 30; i++) {	//弾の配列にできた空白を埋める

				if (bullets[i] == nullptr) { break; }

				bullets[i - 1] = bullets[i];
				bullets[i] = nullptr;
			}
			bulletcount--;
		}
	}

	if (bullets[bulletcount] == nullptr && bulletcount < 30 && Time % 5 == 0) {	//画面上の弾の数は最大値未満？
		bullets[bulletcount] = new straightBlt(GetLocation(), 5, 180);	//真なら弾を発射する
			Time = 0;
		}
}

void Enemy::Draw() {
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, (int)GetRadius(), 0x00ff00);

	for (int i = 0; i < 30; i++) {
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

void Enemy::Hit() {}

bool Enemy::Checkhp() { 
	bool let = (hp <= 0);
	return let;
}

int Enemy::Getpoint() { return point; }
