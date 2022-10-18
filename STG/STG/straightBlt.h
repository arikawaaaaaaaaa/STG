#pragma once
#include "BulletsBase.h"
class straightBlt : public BulletsBase
{
private:
	int image;

public:
	straightBlt(Location loc);	//コンストラクタ

public:
	virtual void Update() override;
	virtual void Draw() override;
};

