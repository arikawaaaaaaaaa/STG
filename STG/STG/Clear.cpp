#include "Clear.h"
#include"Scenemng.h"
#include "Title.h"
#include"dxlib.h"
#include"common.h"
#include "KeyMng.h"

Clear::Clear() {

}


AbstractScene* Clear::Update() {
    if (KeyMng::OnClick(KEY_INPUT_SPACE)) return new Title();

    return this;
}

void Clear::Draw() const {
    DrawString(300, SCREEN_HEIGHT / 2 - 50, "CLEAR", 0xffffff);
    DrawString(300, SCREEN_HEIGHT / 2, "SPACE TO TITLE", 0xffffff);
}