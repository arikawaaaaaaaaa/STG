#pragma once

#include"DxLib.h"
#include"Charabase.h"

class Enemy : public CharaBase, public SphereColider
{
private:
	int hp;
	int point;

public:
	Enemy(Location loc, float rad);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit() override;
	bool Checkhp();
	int Getpoint();

};