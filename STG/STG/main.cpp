#include"Scenemng.h"
#include"main.h"
#include"dxlib.h"


AbstractScene* GameMain::Update() {
    player->Update();

    return this;
}

//GameMain::GameMain() {
//    // 変数の初期設定
//}

void GameMain::Draw() const {
    player->Draw();

    DrawString(200, 300, "GAMEMAIN", 0xffffff);
}