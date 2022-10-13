#pragma once
#include"Scenemng.h"
#include"player.h"

class GameMain :public AbstractScene {
private:
	Player* player;

public:
	GameMain() {
		Location location;
		location.X = 10;
		location.Y = 100;

		float rad = 10.f;
		player = new Player(location, rad);
	}

	virtual ~GameMain() {
		delete player;
	};

	virtual AbstractScene* Update() override;

	virtual void Draw() const override;
};

