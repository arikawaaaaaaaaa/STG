#pragma once

//#include"DxLib.h"
#include"Charabase.h"
#include"ItemBase.h"

class Player : public CharaBase, public SphereColider{

private:

	//‘Ì—Í
	int Life;
	int MaxLife;

	int Score;

	int HitCool;	//”í’e–³“G
	int ShotCool;	//UŒ‚ŠÔŠu

	//©‹@E’e‰æ‘œ
	int image;
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

	//ƒ‰ƒCƒtæ“¾
	int GetLife() { return Life; }
	int GetMaxLife() { return MaxLife; }
};