#pragma once

#include"DxLib.h"
#include"Charabase.h"

class Enemy : public CharaBase
{
public:
	Enemy();
	~Enemy();
	void Draw();

	void Draw() const override;
	CharaBase* Update() override;
	int Hit() override;

	int LifeCheck();
	int GetPoint();

private:

	float X;
	float Y;

	int Life;
	int Score;

};