#pragma once

#include"DxLib.h"
#include"Charabase.h"
#include"player.h"

class Enemy : public CharaBase, public SphereColider
{
private:
	int hp;
	int maxhp;
	int point;

	//プレイヤーの座標
	int PlayerX;
	int PlayerY;

	//攻撃の待機時間など
	int Time;

public:
	Enemy(Location loc, float rad);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit() override;
	//virtual void Hit(int damage);
	void Hit(int damage);				//被弾時
	//void HitPlayer(int BulletCnt);
	bool Checkhp();
	int Getpoint();
	void DeleteBullet(int bulletCnt);	//弾を消す

	void GetPlayerStat(Player* player);	//プレイヤー情報取得

	void SircleShot(int way, int spd, int angle);	//円形ショット(way数、弾速、角度)
	void HomingShot(int spd);						//自機狙い(弾速)
};