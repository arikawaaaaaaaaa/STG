#include"Scenemng.h"
#include"main.h"
#include"dxlib.h"


AbstractScene* GameMain::Update() {
    player->Update();
    for (int i = 0; i < 10; i++) {
        if (enemy[i] == nullptr)break;

        enemy[i]->Update();
    }

    BulletsBase** bullets = player->GetBullets();
    for (int bulletcnt = 0; bulletcnt < 30; bulletcnt++) {
        if (bullets[bulletcnt] == nullptr)break;
        
        for (int enecnt = 0; enecnt < 10; enecnt++) {
            if (enemy[enecnt] == nullptr)break;

            if (bullets[bulletcnt]->HitSphere(enemy[enecnt])) {
                //弾が命中
                player->AddScore(10);
            }
        }
    }

    return this;
}

//GameMain::GameMain() {
//    // 変数の初期設定
//}

void GameMain::Draw() const {
    player->Draw();
    for (int i = 0; i < 10; i++) {
        if (enemy[i] == nullptr)break;

        enemy[i]->Draw();
    }

    DrawFormatString(200, 200, 0xffffff, "%d", player->GetScore());
    DrawString(200, 300, "GAMEMAIN", 0xffffff);
}