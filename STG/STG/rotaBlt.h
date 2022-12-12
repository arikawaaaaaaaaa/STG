#pragma once
#include"BulletsBase.h"

class rotaBlt : public BulletsBase
{
public:
	rotaBlt(Location loc, float spd, int ang);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};

