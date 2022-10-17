/********************************************************************
**	第４章　ゲームプログラミングの基本
**	　ブロック崩しゲームの作成(2018)
********************************************************************/
#include "DxLib.h"
#include "Scenemng.h"
#include "main.h"
#include"KeyMng.h"

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {

    // タイトルを test に変更
    SetMainWindowText("シューティング");

    ChangeWindowMode(TRUE);		// ウィンドウモードで起動

    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

    SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

    SetFontSize(20);		// 文字サイズを設定

    SceneManager sceneMng(new GameMain);

    // ゲームループ
    while (ProcessMessage() == 0 && sceneMng.Update() != nullptr) {

        ClearDrawScreen();		// 画面の初期化

        if (KeyMng::OnPress(KEY_INPUT_RIGHT)) {
            DrawString(100, 100, "aaa", 0xffffff);
        }
        if (KeyMng::OnPress(KEY_INPUT_LEFT)) {
            DrawString(100, 200, "aaa", 0xffffff);
        }
        if (KeyMng::OnPress(KEY_INPUT_UP)) {
            DrawString(100, 300, "aaa", 0xffffff);
        }
        if (KeyMng::OnPress(KEY_INPUT_DOWN)) {
            DrawString(100, 400, "aaa", 0xffffff);
        }

        if (KeyMng::OnClick(KEY_INPUT_RIGHT)) {
            DrawString(200, 100, "aaa", 0xffffff);
        }
        if (KeyMng::OnClick(KEY_INPUT_LEFT)) {
            DrawString(200, 200, "aaa", 0xffffff);
        }
        if (KeyMng::OnClick(KEY_INPUT_UP)) {
            DrawString(200, 300, "aaa", 0xffffff);
        }
        if (KeyMng::OnClick(KEY_INPUT_DOWN)) {
            DrawString(200, 400, "aaa", 0xffffff);
        }

        if (KeyMng::OnRelease(KEY_INPUT_RIGHT)) {
            DrawString(300, 100, "aaa", 0xffffff);
        }
        if (KeyMng::OnRelease(KEY_INPUT_LEFT)) {
            DrawString(300, 200, "aaa", 0xffffff);
        }
        if (KeyMng::OnRelease(KEY_INPUT_UP)) {
            DrawString(300, 300, "aaa", 0xffffff);
        }
        if (KeyMng::OnRelease(KEY_INPUT_DOWN)) {
            DrawString(300, 400, "aaa", 0xffffff);
        }

        sceneMng.Draw();

        ScreenFlip();			// 裏画面の内容を表画面に反映

    }

    DxLib_End();	// DXライブラリ使用の終了処理

    return 0;	// ソフトの終了
}