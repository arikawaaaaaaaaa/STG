#pragma once
#include "BulletsBase.h"

class reflecBlt : public BulletsBase
{
private:
	int image;
	int Refcnt;

public:
	reflecBlt(Location loc, float spd, float ang, int ref);	//�R���X�g���N�^

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};


