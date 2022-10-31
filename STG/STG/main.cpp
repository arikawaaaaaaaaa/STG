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
                enemy[enecnt]->Hit(bullets[bulletcnt]->GetDamage());

                player->Hit(bulletcnt); //弾を消す
                bullets = player->GetBullets();
                bulletcnt--;

                if (enemy[enecnt]->Checkhp()) {
                    player->AddScore(enemy[enecnt]->Getpoint());

                    delete enemy[enecnt];		//出た弾を消す
                    enemy[enecnt] = nullptr;

                    for (int i = enecnt + 1; i < 10; i++) {	//弾の配列にできた空白を埋める

                        if (enemy[i] == nullptr) { break; }

                        enemy[i - 1] = enemy[i];
                        enemy[i] = nullptr;
                    }
                    enecnt--;
                }
            }
        }
    }

    time++;
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