#pragma once
#include"DxLib.h"

class KeyMng
{
private:
	static int OldKey;	//�O�t���[������
	static int NowKey;	//���t���[������

private:
	KeyMng() = default;

public:

	static void Update() {
		OldKey = NowKey;
		NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	//�{�^�����������u�Ԃ���TRUE
	static bool OnClick(int input) {
		int flg = (NowKey & ~OldKey);
		bool let = (flg & input);
		return let;
	}

	//�{�^����������Ă����TRUE
	static bool OnPress(int input) {
		bool let = (NowKey & input);
		return let;
	}

	//�{�^���𗣂����u�Ԃ���TRUE
	static bool OnRelease(int input) {
		int flg = (OldKey & ~NowKey);
		bool let = (flg & input);
		return let;
	}
};