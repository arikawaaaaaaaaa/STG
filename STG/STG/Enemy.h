#pragma once

#include"DxLib.h"
#include"Charabase.h"
#include"player.h"

struct Moveinfo {
int pattern;	//行動パターン
Location Point;	//目的地
Location Speed;	//スピード
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

	int phase;	//進行度

	//プレイヤーの座標
	int PlayerX;
	int PlayerY;

	//攻撃の待機時間など
	int Time;
	int angle;

	int bullet_A[8];
	int bullet_B[8];
	int bullet_C[8];

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

	Location GetLoc() { return GetLocation(); }
	int GetLife() { return hp; }

	//攻撃パターン読み込み
	void inputCSV();

	void Move();

	void GetPlayerStat(Player* player);	//プレイヤー情報取得

	void SircleShot(Location loc, int way, float spd, float angle, int col);	//円形ショット(way数、弾速、角度、色)

	//円形反射ショット(way数、弾速、角度、各方向の壁で反射するか(それぞれ上、右、下、左方向)、色)
	void SirclerefShot(Location loc, int way, int spd, float angle, bool up, bool right, bool down, bool left, int col);

	void HomingShot(Location loc, float spd, int ang, int col);						//自機狙い(弾速、ずらし、色)

	 //一度止まるショット(弾速、初めの速度、止まるまでの時間、待機時間、次の速度,次の弾速)
	void StopShot(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd, int col);

	//一度止まる円形ショット(way数、初めの速度、初めの角度、止まるまでの時間、待機時間、次の角度、次の弾速、Reangをway数に応じて変化させるか、色)
	void SircleStopShot(Location loc, int way, int Stspd, float Stang, int stop, int time, int Reang, int Respd, bool ChangeReang, int col);
};