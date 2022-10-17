#include"Scenemng.h"
#include"KeyMng.h"
#include"DxLib.h"

AbstractScene* SceneManager::Update() {

    //キー入力更新
    KeyMng::Update();

    //現在シーンのアップデート
    AbstractScene* p = mScene->Update();

    //シーン切り替え
    if (p != mScene) {
        delete mScene;
        mScene = p;
    }
    return p;
}

void SceneManager::Draw() const {
    mScene->Draw();
}

