#pragma once
#include"SphereColider.h"

constexpr auto PI = 3.1415926f;

struct RefWall
{
	bool UP;
	bool RIGHT;
	bool DOWN;
	bool LEFT;
};

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
	virtual bool isDeath() = 0;
	virtual int GetDamage();
};

