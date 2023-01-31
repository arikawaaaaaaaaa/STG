#pragma once

#include"DxLib.h"
#include"Charabase.h"
#include"player.h"

struct Moveinfo {
int pattern;	//行動パターン
Location Point;	//目的地
int nextPointnum;	//次の配列番号
int Waittime;	//待ち時間
int  attack;	//攻撃の種類
};

class Enemy : public CharaBase, public SphereColider
{
private:
	int hp;
	int maxhp;
	int point;

	int shotnum;

	//プレイヤーの座標
	int PlayerX;
	int PlayerY;

	//攻撃の待機時間など
	int Time;

	//攻撃パターン
	Moveinfo moveinfo[9];
	int current;
	int waittime;

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

	//攻撃パターン読み込み
	void inputCSV();

	void Move();

	void GetPlayerStat(Player* player);	//プレイヤー情報取得

	void SircleShot(Location loc, int way, int spd, float angle);	//円形ショット(way数、弾速、角度)

	//円形反射ショット(way数、弾速、角度、各方向の壁で反射するか(それぞれ上、右、下、左方向))
	void SirclerefShot(Location loc, int way, int spd, float angle, bool up, bool right, bool down, bool left);

	void HomingShot(Location loc, int spd);						//自機狙い(弾速)

	 //一度止まるショット(弾速、初めの速度、止まるまでの時間、待機時間、次の速度,次の弾速)
	void StopShot(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd);

	//一度止まる円形ショット(弾速、way数、色、初めの速度、止まるまでの時間、待機時間、次の角度、次の弾速、Reangをway数に応じて変化させるか)
	void SircleStopShot(Location loc, int way, int Stspd, float Stang, int stop, int time, int Reang, int Respd, bool ChangeReang);
};