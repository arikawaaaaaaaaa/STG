#pragma once

#include"DxLib.h"
#include"Charabase.h"

class Player : public CharaBase
{
public:
	Player();
	~Player();
	void Draw();

	void Draw() const override;
	CharaBase* Update() override;
	int Hit() override;

	int LifeCheck();
	int GetScore();

private:

	float X;
	float Y;

	int Life;
	int Score;

};