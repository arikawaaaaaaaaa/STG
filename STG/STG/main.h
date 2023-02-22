#pragma once
#include"Scenemng.h"
#include"player.h"
#include"Enemy.h"
#include"ItemBase.h"
#include"common.h"

typedef enum RESULT {
	NONE,
	CLEAR,
	OVER
};

class GameMain :public AbstractScene {
private:
	Player* player;
	Enemy** enemy;
	ItemBase** items;

	int image;

	int time;
	RESULT CheckEnd;

public:
    GameMain() {
        Location location;
        location.X = SCREEN_WIDTH / 2;
        location.Y = SCREEN_HEIGHT / 2 + 200;

        time = 0;
        CheckEnd = NONE;

        float rad = 5.f;
        player = new Player(location, rad);

        enemy = new Enemy * [10];
        for (int i = 0; i < 10; i++) {
            enemy[i] = nullptr;
        }
        enemy[0] = new Enemy(Location{ -100,-100 }, 20);

        items = new ItemBase * [10];
        for (int i = 0; i < 10; i++) {
            items[i] = nullptr;
        }

        image = LoadGraph("images/BackGround.png");
    }


	virtual ~GameMain() {
		delete player;
	};

	virtual AbstractScene* Update() override;

	virtual void Draw() const override;
};

