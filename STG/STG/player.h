#pragma once

//#include"DxLib.h"
#include"Charabase.h"
#include"ItemBase.h"

class Player : public CharaBase, public SphereColider{

private:

	int Life;
	int Score;

	int ShotCool;

	int bullet[8];

public:
	Player(Location loc, float rad);
	//~Player();

	void Update() override;
	void Draw() override;
	void Hit() override;

	void Hit(int BulletCnt);
	void Hit(class ItemBase* item);

	bool LifeCheck();
	int GetScore();
	void AddScore(int add) { if (add > 0) Score += add; }


};