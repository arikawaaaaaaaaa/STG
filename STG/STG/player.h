#pragma once

//#include"DxLib.h"
#include"Charabase.h"

class Player : public CharaBase, public SphereColider{

private:

	int Life;
	int Score;

public:
	Player(Location loc, float rad);
	//~Player();

	void Update() override;
	void Draw() override;
	void Hit() override;
	void Hit(int BulletCnt);

	bool LifeCheck();
	int GetScore();
	void AddScore(int add) { if (add > 0) Score += add; }

};