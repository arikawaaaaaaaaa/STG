#pragma once
#include "BulletsBase.h"

class bigBlt : public BulletsBase
{
private:
	int image[8];
	int color;
	float DrawAng;

	int Refcnt;

	RefWall wall;

public:
	bigBlt(Location loc, float spd, float ang, int ref, bool up, bool right, bool down, bool left, int col, int img[8]);	//�R���X�g���N�^

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};
