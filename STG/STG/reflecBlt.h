#pragma once
#include "BulletsBase.h"

struct RefWall
{
	bool UP;
	bool RIGHT;
	bool DOWN;
	bool LEFT;
};

class reflecBlt : public BulletsBase
{
private:
	int image;
	int Refcnt;

	RefWall wall;

public:
	reflecBlt(Location loc, float spd, float ang, int ref, bool up, bool right, bool down, bool left);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};


