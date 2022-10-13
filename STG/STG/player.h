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

	bool LifeCheck();
	int GetScore();

};