#pragma once
#include "BulletsBase.h"

class straightBlt : public BulletsBase
{
private:
	int image[8];
	int color;

	float DrawAng;

public:
	straightBlt(Location loc, float spd, float ang, int col);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};

