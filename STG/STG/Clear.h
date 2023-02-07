#pragma once
#include "Scenemng.h"
class Clear : public AbstractScene
{
public:

	Clear();
	virtual AbstractScene* Update() override;
	virtual void Draw() const override;
};

