#pragma once

#include"DxLib.h"
#include"Charabase.h"

class Enemy : public CharaBase, public SphereColider
{
private:
	int hp;
	int point;

	int Time;

public:
	Enemy(Location loc, float rad);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit() override;
	//virtual void Hit(int damage);
	void Hit(int BulletCnt);
	bool Checkhp();
	int Getpoint();

};