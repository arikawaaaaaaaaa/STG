#pragma once
#include "BulletsBase.h"

constexpr auto PI = 3.1415926f;

class straightBlt : public BulletsBase
{
private:
	int image;

public:
	straightBlt(Location loc, int spd, float ang);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};

