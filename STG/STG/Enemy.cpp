#include"DxLib.h"
#include "enemy.h"

Enemy::Enemy (Location loc, float rad) : SphereColider(loc, rad) {
	point = 10;
	hp = 10;

	//point‰Šú‰»
	//hp‰Šú‰»

	speed = Location{ 0,1 };

	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++) {
		bullets[i] = nullptr;
	}
}

void Enemy::Update() {
	Location NewLoc = GetLocation();
	NewLoc.Y += speed.Y;
	SetLocation(NewLoc);
}

void Enemy::Draw() {
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, (int)GetRadius(), 0x00ff00);
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
