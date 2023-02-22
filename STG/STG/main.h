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

    bool ExEnemy;       //敵はいる？
    int Stage;          //現在ステージ
    int SceneChange;    //背景描画
    int Changeflg;

	int image[2];

	int time;
	RESULT CheckEnd;

public:
    GameMain() {
        Location location;
        location.X = SCREEN_WIDTH / 2;
        location.Y = SCREEN_HEIGHT / 2 + 200;

        Stage = 0;
        ExEnemy = false;
        SceneChange = 0;
        Changeflg = 0;

        time = 0;
        CheckEnd = NONE;

        float rad = 5.f;
        player = new Player(location, rad);

        enemy = new Enemy * [10];
        for (int i = 0; i < 10; i++) {
            enemy[i] = nullptr;
        }

        items = new ItemBase * [10];
        for (int i = 0; i < 10; i++) {
            items[i] = nullptr;
        }

        image[0] = LoadGraph("images/BackGround.png");
        image[1] = LoadGraph("images/back_b.png");
    }


	virtual ~GameMain() {
		delete player;
	};

	virtual AbstractScene* Update() override;

	virtual void Draw() const override;
};

