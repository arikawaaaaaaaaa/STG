#pragma once
#include"Scenemng.h"
#include"player.h"

class GameMain :public AbstractScene {
private:
	Player player;

public:
	GameMain();
	virtual ~GameMain() {};

	virtual AbstractScene* Update() override;

	virtual void Draw() const override;
};

