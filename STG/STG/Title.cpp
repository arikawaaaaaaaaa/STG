#include"Scenemng.h"
#include "Title.h"
#include"main.h"
#include"dxlib.h"
#include"common.h"
#include "KeyMng.h"

Title::Title() {

}


AbstractScene* Title::Update() {
    if (KeyMng::OnClick(KEY_INPUT_SPACE)) return new GameMain();

    return this;
}

void Title::Draw() const{
    DrawString(300, SCREEN_HEIGHT / 2 - 50, "TITLE", 0xffffff);
    DrawString(300, SCREEN_HEIGHT / 2, "SPACE TO START", 0xffffff);
}