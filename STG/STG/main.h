#pragma once
#include"Scenemng.h"

class GameMain :public AbstractScene {
private:

public:
	GameMain();
	virtual ~GameMain() {};

	virtual AbstractScene* Update() override;

	virtual void Draw() const override;
};

