#pragma once
#include"DxLib.h"

class KeyMng
{
private:
	static char OldKey[256];	//前フレーム入力
	static char NowKey[256];	//今フレーム入力

private:
	KeyMng() = default;

public:

	static void Update() {

		for (int i = 0; i < 256; i++) {
			OldKey[i] = NowKey[i];
		}

		if (GetHitKeyStateAll(NowKey) == -1) {
			throw -1;	//キー入力を正常に取れなければ終了
		}
		//NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	//ボタンを押した瞬間だけTRUE
	static bool OnClick(int input) {
		//int flg = (NowKey[input] == 1 && OldKey[input] == 0);
		bool let = (NowKey[input] == 1 && OldKey[input] == 0);
		return let;
	}

	//ボタンが押されている間TRUE
	static bool OnPress(int input) {
		bool let = (NowKey[input] == 1);
		return let;
	}

	//ボタンを離した瞬間だけTRUE
	static bool OnRelease(int input) {
		//int flg = (OldKey[input] == 1 && NowKey[input] == 0);
		bool let = (OldKey[input] == 1 && NowKey[input] == 0);
		return let;
	}
};