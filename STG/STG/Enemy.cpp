#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "KeyMng.h"

Enemy::Enemy (Location loc, float rad) : SphereColider(loc, rad) {
	point = 10;
	hp = 10;

	Time = 0;

	//point������
	//hp������

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

		if (bullets[bulletcount]->isDeath()) {	//�e����ʊO�ɏo���H

			delete bullets[bulletcount];		//�o���e������
			bullets[bulletcount] = nullptr;

			for (int i = bulletcount + 1; i < 30; i++) {	//�e�̔z��ɂł����󔒂𖄂߂�

				if (bullets[i] == nullptr) { break; }

				bullets[i - 1] = bullets[i];
				bullets[i] = nullptr;
			}
			bulletcount--;
		}
	}

	if (bullets[bulletcount] == nullptr && bulletcount < 30 && Time % 5 == 0) {	//��ʏ�̒e�̐��͍ő�l�����H
		bullets[bulletcount] = new straightBlt(GetLocation(), 5, 180);	//�^�Ȃ�e�𔭎˂���
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
