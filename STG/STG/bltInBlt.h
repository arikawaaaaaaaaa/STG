#pragma once
#include "BulletsBase.h"
#include "common.h"
#include "Enemy.h"

class bltInBlt : public BulletsBase
{
private:
	int image;

public:
	bltInBlt(Location loc, float spd, float ang);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};

