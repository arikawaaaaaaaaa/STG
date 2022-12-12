#pragma once
#include "BulletsBase.h"

class reflecBlt : public BulletsBase
{
private:
	int image;
	int Refcnt;

public:
	reflecBlt(Location loc, float spd, float ang, int ref);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};


