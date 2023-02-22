#include"Scenemng.h"
#include"main.h"
#include"Clear.h"
#include"Gameover.h"
#include"dxlib.h"
#include"HPotion.h"
#include"common.h"


AbstractScene* GameMain::Update() {

    if (!CheckEnd)player->Update();

    for (int i = 0; i < 10; i++) {
        if (enemy[i] == nullptr)break;

        enemy[i]->Update();
        enemy[i]->GetPlayerStat(player);
    }
    for (int i = 0; i < 10; i++) {
        if (items[i] == nullptr)break;

        items[i]->Update();
    }

    //弾と敵の当たり
    BulletsBase** bullets = player->GetBullets();
    for (int enecnt = 0; enecnt < 10; enecnt++) {
        
        for (int bulletcnt = 0; bulletcnt < BltLimit; bulletcnt++) {

            if (enemy[enecnt] == nullptr)break;
            if (bullets[bulletcnt] == nullptr)break;

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
                            break;
                        }
                    }

                    delete enemy[enecnt];		//敵を消す
                    enemy[enecnt] = nullptr;


                    for (int i = enecnt + 1; i < 10; i++) {	//敵の配列にできた空白を埋める

                        if (enemy[i] == nullptr) { break; }

                        enemy[i - 1] = enemy[i];
                        enemy[i] = nullptr;
                    }
                }
            }
        }
    }

    //弾とプレイヤーの当たり
    for (int ene = 0; ene < 10; ene++) {

        if (enemy[ene] == nullptr)break;

        BulletsBase** bullets = enemy[ene]->GetBullets();
        for (int bulletcnt = 0; bulletcnt < BltLimit; bulletcnt++) {
            if (bullets[bulletcnt] == nullptr)break;

            if (bullets[bulletcnt]->HitSphere(player)) {
                //弾が命中
                player->Hit();

                enemy[ene]->DeleteBullet(bulletcnt); //弾を消す
                bullets = enemy[ene]->GetBullets();
                bulletcnt--;
            }
        }
    }

    //アイテムの当たり
    for (int itemcnt = 0; itemcnt < 10; itemcnt++) {
        if (items[itemcnt] == nullptr)break;

        if (player->HitSphere(items[itemcnt])) {

            player->Hit(items[itemcnt]);

            delete items[itemcnt];		//アイテムを消す
            items[itemcnt] = nullptr;


            for (int i = itemcnt + 1; i < 10; i++) {	//アイテムの配列にできた空白を埋める

                if (items[i] == nullptr) { break; }

                items[i - 1] = items[i];
                items[i] = nullptr;
            }
            itemcnt--;
        }
        else if (items[itemcnt]->IsDeath()) {

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

    if (!CheckEnd) {
        int i = 0;
        for (i = 0; i < 10; i++) {
            if (enemy[i] != nullptr || items[i] != nullptr) break;
        }
        if (i == 10) {
            CheckEnd = CLEAR;
            time = 0;
        }
        if (player->LifeCheck()) {
            CheckEnd = OVER;
            time = 0;
        }
    }
    else if (180 < time) {
        if (CheckEnd == CLEAR)return new Clear();
        if (CheckEnd == OVER)return new Gameover();
    }

    return this;
}

//GameMain::GameMain() {
//    // 変数の初期設定
//}

void GameMain::Draw() const {

    DrawGraph(0, 0, image, false);

    //プレイヤーの描画
    if (!player->LifeCheck())player->Draw();

    //敵の描画
    for (int i = 0; i < 10; i++) {
        if (enemy[i] == nullptr)break;

        enemy[i]->Draw();
    }

    //アイテムの描画
    for (int i = 0; i < 10; i++) {
        if (items[i] == nullptr)break;

        items[i]->Draw();
    }

    //ゲーム画面の描画
    DrawBoxAA(0, 0, SCREEN_MARGIN, SCREEN_HEIGHT, 0xadd8e6, true);
    DrawBoxAA(SCREEN_WIDTH - SCREEN_MARGIN, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xadd8e6, true);

    DrawFormatString(200, 50, 0xffffff, "%d", player->GetScore());
    DrawString(200, 0, "GAMEMAIN", 0xffffff);

    for (int i = 0; i < 10; i++) {
        if (enemy[i] == nullptr)break;

        DrawFormatString(200, 200 + 50 * i, 0xff0000, "%d", enemy[i]->GetLife());
    }

    //体力ゲージ表示
    //赤いとこ
    DrawBoxAA(SCREEN_WIDTH - SCREEN_MARGIN + 50, 100,
              SCREEN_WIDTH - SCREEN_MARGIN + 80, SCREEN_HEIGHT - 100, 0xff0000, true);

    //緑のとこ
    if (player->GetLife() < player->GetMaxLife()) {
    DrawBoxAA(SCREEN_WIDTH - SCREEN_MARGIN + 50, SCREEN_HEIGHT - 100 - (520 / player->GetMaxLife() * (player->GetLife())), 
              SCREEN_WIDTH - SCREEN_MARGIN + 80, SCREEN_HEIGHT - 100, 0x67ff00, true);
    }
    else {
        DrawBoxAA(SCREEN_WIDTH - SCREEN_MARGIN + 50, SCREEN_HEIGHT - 100 - 520,
                  SCREEN_WIDTH - SCREEN_MARGIN + 80, SCREEN_HEIGHT - 100, 0x67ff00, true);
    }

    //体力最大値以上の表示
    if (player->GetMaxLife() < player->GetLife()){
        DrawBoxAA(SCREEN_WIDTH - SCREEN_MARGIN + 50, SCREEN_HEIGHT - 100 - (520 / player->GetMaxLife() * (player->GetLife() - player->GetMaxLife())), 
            SCREEN_WIDTH - SCREEN_MARGIN + 80, SCREEN_HEIGHT - 100, 0x00ffff, true);
    }
}