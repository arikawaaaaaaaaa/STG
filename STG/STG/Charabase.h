#pragma once
#include"SphereColider.h"

class CharaBase : public SphereColider{
private:
	int bullets[500];
	float speed;
	int image[6];

public:

	virtual ~CharaBase() {};
	virtual CharaBase* Update();
	virtual void Draw() const;
	virtual int Hit();
	
	int GetBullets();
	void SetSpeed(float spd);
	void SetImage(int img);
};