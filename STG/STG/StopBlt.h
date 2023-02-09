#pragma once
#include "BulletsBase.h"

class StopBlt : public BulletsBase	//一度止まって方向転換する弾
{
private:
	int image[8];
	int color;

	float DrawAng;

	int spd;			//弾速
	Location StSpd;	//初期速度
	int Respd;		//方向転換後の速度
	int Reang;		//方法転換後の角度
	int time;		//経過時間
	int StopTime;	//止まるまでの時間(flame)
	int WaitTime;	//止まってから動き出すまでの時間(flame)

public:
	StopBlt(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd, int col);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};

