#include"DxLib.h"
#include "enemy.h"
#include "straightBlt.h"
#include "KeyMng.h"
#include"common.h"

#include<math.h>

Enemy::Enemy (Location loc, float rad) : SphereColider(loc, rad) {
	point = 10;
	hp = 10;
	maxhp = hp;

	Time = 0;

	//point‰Šú‰»
	//hp‰Šú‰»

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

		if (bullets[bulletcount]->isDeath()) {	//’e‚ª‰æ–ÊŠO‚Éo‚½H

			DeleteBullet(bulletcount);	//’e‚ğÁ‚·
			bulletcount--;
		}
	}

	int AttackTime = 10;	//UŒ‚ŠÔŠu
	if (bullets[bulletcount] == nullptr && bulletcount < BltLimit && Time % AttackTime == 0) {	//‰æ–Êã‚Ì’e‚Ì”‚ÍÅ‘å’l–¢–H
		switch (hp)
		{
		case 10:
			SircleShot(8, 3, GetRand(360));
			break;

		case 9:
			HomingShot(3);
			break;

		default:
			break;
		}
		Time = 0;
	}
}

void Enemy::Draw() {	//•`‰æ
	int X = (int)GetLocation().X;
	int Y = (int)GetLocation().Y;
	int Rad = (int)GetRadius();

	float size = 30;

	//‘Ì—Íƒo[

	//Ô‚¢‚Æ‚±
	DrawBox(X - size, Y - Rad - 10,
			X + size, Y - Rad - 15, 0xff0000, TRUE);

	//—Î‚Ì‚Æ‚±
	DrawBox(X - size, Y - Rad - 10,
			(X - size) + size * 2 * ((float)hp / maxhp), Y - Rad - 15, 0x00ff00, TRUE);

	DrawCircle(X, Y, Rad, 0x00ff00);	//“G–{‘Ì

	for (int i = 0; i < BltLimit; i++) {	//’e
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}
}

void Enemy::Hit(int damage) {	//”í’e

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
//	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//’e‚Ì”z—ñ‚É‚Å‚«‚½‹ó”’‚ğ–„‚ß‚é
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

void Enemy::DeleteBullet(int BulletCnt) {		//’e‚ğÁ‚·

	delete bullets[BulletCnt];
	bullets[BulletCnt] = nullptr;

	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//’e‚Ì”z—ñ‚É‚Å‚«‚½‹ó”’‚ğ–„‚ß‚é

		if (bullets[i] == nullptr) { break; }

		bullets[i - 1] = bullets[i];
		bullets[i] = nullptr;
	}
}

void Enemy::GetPlayerStat(Player* player) {		//ƒvƒŒƒCƒ„[‚ÌÀ•W‚ğæ“¾

	PlayerX = player->GetLocation().X;
	PlayerY = player->GetLocation().Y;
}

void Enemy::SircleShot(int way, int spd, int ang) {		//‰~Œ`ƒVƒ‡ƒbƒg(way”A’e‘¬AŠp“x)
	int shot = 0;	//’e‚ğ”­Ë‚µ‚½”

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new straightBlt(GetLocation(), spd, ang);	//’e‚ğ”­Ë‚·‚é
			shot++;				//”­Ë‚µ‚½”‚ğ‘‚â‚·
			ang += (360 / way);	//Šp“x‚ğ’²®‚·‚é
		}

	}

}

void Enemy::HomingShot(int spd) {		//©‹@‘_‚¢(’e‘¬)

	//ƒvƒŒƒCƒ„[ŠÔ‚ÌŠp“xæ“¾------
	double tan = atan2(((double)PlayerY - GetLocation().Y),
		(double)PlayerX - GetLocation().X);

	int ang = (int)(tan * 180 / PI) + 90;
	//----------------------------

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new straightBlt(GetLocation(), spd, ang);	//’e‚ğ”­Ë‚·‚é
			break;
		}
	}
}