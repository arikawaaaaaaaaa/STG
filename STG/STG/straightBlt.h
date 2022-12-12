#pragma once
#include "BulletsBase.h"

class straightBlt : public BulletsBase
{
private:
	int image;

public:
	straightBlt(Location loc, float spd, float ang);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};

