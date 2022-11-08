#include"Scenemng.h"
#include"main.h"
#include"dxlib.h"
#include"HPotion.h"


AbstractScene* GameMain::Update() {

    player->Update();
    for (int i = 0; i < 10; i++) {
        if (enemy[i] == nullptr)break;

        enemy[i]->Update();
    }
    for (int i = 0; i < 10; i++) {
        if (items[i] == nullptr)break;

        items[i]->Update();
    }

    //弾と敵の当たり
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

                if (enemy[enecnt]->Checkhp()) {     //敵が倒された
                    player->AddScore(enemy[enecnt]->Getpoint());

                    for (int i = 0; i < 10; i++) {
                        if (items[i] == nullptr) {
                            items[i] = new HPotion(enemy[enecnt]->GetLocation());
                        }
                    }

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

    //アイテムの当たり
    for (int itemcnt = 0; itemcnt < 10; itemcnt++) {
        if (items[itemcnt] == nullptr)break;

        if (player->HitSphere(items[itemcnt])) {
            delete items[itemcnt];		//アイテムを消す
            items[itemcnt] = nullptr;


            for (int i = itemcnt + 1; i < 10; i++) {	//アイテムの配列にできた空白を埋める

                if (items[i] == nullptr) { break; }

                items[i - 1] = items[i];
                items[i] = nullptr;
            }
            itemcnt--;
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

    for (int i = 0; i < 10; i++) {
        if (items[i] == nullptr)break;

        items[i]->Draw();
    }

    DrawFormatString(200, 200, 0xffffff, "%d", player->GetScore());
    DrawString(200, 300, "GAMEMAIN", 0xffffff);
}