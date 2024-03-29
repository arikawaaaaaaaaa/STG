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

	//体力関連
	int hparray[6] = { 100,100,100,100,30,50 };
	int hp;
	int maxhp;

	int point;

	int Stage;

	//画像
	int image[4];

	int shotnum;

	int phase;	//進行度

	//前フレームの座標
	Location Old;

	//プレイヤーの座標
	int PlayerX;
	int PlayerY;

	//攻撃の待機時間など
	int Time;
	int angle;

	//弾の画像データ
	int bullet_A[8];
	int bullet_B[8];
	int bullet_C[8];
	int bullet_D[8];

	//攻撃パターン
	Moveinfo moveinfo[9];
	int current;
	int waittime;

public:
	Enemy(Location loc, float rad, int stage);

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

	void CreateShot(Location loc, float spd, float angle, int col);	//直進ショット(弾速、角度、色)

	void CircleShot(Location loc, int way, float spd, float angle, int col);	//円形ショット(way数、弾速、角度、色)

	//巨大ショット(弾速、角度、各方向の壁で反射するか(それぞれ上、右、下、左方向)、色)
	void BigShot(Location loc, int spd, float angle, bool up, bool right, bool down, bool left, int col);

	//円形反射ショット(way数、弾速、角度、各方向の壁で反射するか(それぞれ上、右、下、左方向)、色)
	void CirclerefShot(Location loc, int way, int spd, float angle, bool up, bool right, bool down, bool left, int col);

	void HomingShot(Location loc, float spd, int ang, int col);						//自機狙い(弾速、ずらし、色)

	 //一度止まるショット(弾速、初めの速度、止まるまでの時間、待機時間、次の速度,次の弾速)
	void StopShot(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd, int col);

	//一度止まる円形ショット(way数、初めの速度、初めの角度、止まるまでの時間、待機時間、次の角度、次の弾速、Reangをway数に応じて変化させるか、色)
	void CircleStopShot(Location loc, int way, int Stspd, float Stang, int stop, int time, int Reang, int Respd, bool ChangeReang, int col);
};