#pragma once
#include "Scenemng.h"
class Title : public AbstractScene
{

public:

	Title();
	virtual AbstractScene* Update() override;
	virtual void Draw() const override;
};

