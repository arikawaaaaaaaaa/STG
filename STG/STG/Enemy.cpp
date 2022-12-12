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

	int AttackTime = 0;	//UŒ‚ŠÔŠu
	if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {	//‰æ–Êã‚Ì’e‚Ì”‚ÍÅ‘å’l–¢–H
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

void Enemy::SircleShot(Location loc, int way, int spd, float ang, bool ref) {		//‰~Œ`ƒVƒ‡ƒbƒg(way”A’e‘¬AŠp“xA”½Ë‚·‚é‚©)
	int shot = 0;	//’e‚ğ”­Ë‚µ‚½”

	for (int bulletcount = 0; bulletcount < BltLimit && shot < way; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {

			if (!ref)bullets[bulletcount] = new straightBlt(loc, spd, ang);	//’e‚ğ”­Ë‚·‚é
			else bullets[bulletcount] = new reflecBlt(loc, spd, ang, 1);	//’e‚ğ”­Ë‚·‚é

			shot++;				//”­Ë‚µ‚½”‚ğ‘‚â‚·
			ang += (360.f / way);	//Šp“x‚ğ’²®‚·‚é
		}

	}

}

void Enemy::HomingShot(Location loc, int spd) {		//©‹@‘_‚¢(’e‘¬)

	//ƒvƒŒƒCƒ„[ŠÔ‚ÌŠp“xæ“¾------
	double tan = atan2(((double)PlayerY - loc.Y),
		(double)PlayerX - loc.X);

	int ang = (int)(tan * 180 / PI) + 90;
	//----------------------------

	for (int bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {
			bullets[bulletcount] = new straightBlt(loc, spd, ang);	//’e‚ğ”­Ë‚·‚é
			break;
		}
	}
}