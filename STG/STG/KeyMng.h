#pragma once
#include"DxLib.h"

class KeyMng
{
private:
	static int OldKey;	//前フレーム入力
	static int NowKey;	//今フレーム入力

private:
	KeyMng() = default;

public:

	static void Update() {
		OldKey = NowKey;
		NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	//ボタンを押した瞬間だけTRUE
	static bool OnClick(int input) {
		int flg = (NowKey & ~OldKey);
		bool let = (flg & input);
		return let;
	}

	//ボタンが押されている間TRUE
	static bool OnPress(int input) {
		bool let = (NowKey & input);
		return let;
	}

	//ボタンを離した瞬間だけTRUE
	static bool OnRelease(int input) {
		int flg = (OldKey & ~NowKey);
		bool let = (flg & input);
		return let;
	}
};