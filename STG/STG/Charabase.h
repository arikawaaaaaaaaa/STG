#pragma once
#include"SphereColider.h"
#include"BulletsBase.h"

class CharaBase{
protected:
	Location speed;			//‘¬“x
	BulletsBase** bullets;	//’e

	//int* bullets;
	int* image = nullptr;

public:

	virtual ~CharaBase();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Hit() = 0;

	Location GetSpeed();
	void SetSpeed(Location speed);
	
	BulletsBase** GetBullets();
	//void SetImage(int img);
};