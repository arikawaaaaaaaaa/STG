#pragma once
#include "Scenemng.h"
class Gameover : public AbstractScene
{
public:

	Gameover();
	virtual AbstractScene* Update() override;
	virtual void Draw() const override;
};

