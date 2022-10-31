#pragma once
#include"Scenemng.h"
#include"player.h"
#include"Enemy.h"

class GameMain :public AbstractScene {
private:
	Player* player;
	Enemy** enemy;

	int time;

public:
	GameMain() {
		Location location;
		location.X = 10;
		location.Y = 100;

		time = 0;

		float rad = 5.f;
		player = new Player(location, rad);
		enemy = new Enemy*[10];
		for (int i = 0; i < 10; i++) {
			enemy[i] = nullptr;
		}
		enemy[0] = new Enemy(Location{ (float)GetRand(1280),0 }, 20);
	}

	virtual ~GameMain() {
		delete player;
	};

	virtual AbstractScene* Update() override;

	virtual void Draw() const override;
};

