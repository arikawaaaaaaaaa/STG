#pragma once
#include"SphereColider.h"

class BulletsBase : public SphereColider
{
protected:
	int damage;
	Location speed;

public:
	BulletsBase(Location loc, float rad, int dmg, Location spd) :SphereColider(loc, rad), damage(dmg), speed(spd) {}

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual int GetDamage();
};
