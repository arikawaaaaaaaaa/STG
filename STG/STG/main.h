#pragma once
#include"Scenemng.h"
#include"player.h"
#include"Enemy.h"
#include"ItemBase.h"

class GameMain :public AbstractScene {
private:
	Player* player;
	Enemy** enemy;
	ItemBase** items;

	int time;

public:
	GameMain() {
		Location location;
		location.X = 1280 / 2;
		location.Y = 650;

		time = 0;

		float rad = 5.f;
		player = new Player(location, rad);

		enemy = new Enemy*[10];
		for (int i = 0; i < 10; i++) {
			enemy[i] = nullptr;
		}
		enemy[0] = new Enemy(Location{ 1280 / 2,720 / 2 }, 20);

		items = new ItemBase * [10];
		for (int i = 0; i < 10; i++) {
			items[i] = nullptr;
		}
	}

	virtual ~GameMain() {
		delete player;
	};

	virtual AbstractScene* Update() override;

	virtual void Draw() const override;
};

