#pragma once
#include"SphereColider.h"

class CharaBase{
protected:
	Location speed;

	//int* bullets;
	int* image = nullptr;

public:

	virtual ~CharaBase();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Hit() = 0;

	Location GetSpeed();
	void SetSpeed(Location speed);
	
	//int GetBullets();
	//void SetImage(int img);
};