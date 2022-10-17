#pragma once
#include"DxLib.h"

class KeyMng
{
private:
	static char OldKey[256];	//�O�t���[������
	static char NowKey[256];	//���t���[������

private:
	KeyMng() = default;

public:

	static void Update() {

		for (int i = 0; i < 256; i++) {
			OldKey[i] = NowKey[i];
		}

		if (GetHitKeyStateAll(NowKey) == -1) {
			throw -1;	//�L�[���͂𐳏�Ɏ��Ȃ���ΏI��
		}
		//NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	//�{�^�����������u�Ԃ���TRUE
	static bool OnClick(int input) {
		//int flg = (NowKey[input] == 1 && OldKey[input] == 0);
		bool let = (NowKey[input] == 1 && OldKey[input] == 0);
		return let;
	}

	//�{�^����������Ă����TRUE
	static bool OnPress(int input) {
		bool let = (NowKey[input] == 1);
		return let;
	}

	//�{�^���𗣂����u�Ԃ���TRUE
	static bool OnRelease(int input) {
		//int flg = (OldKey[input] == 1 && NowKey[input] == 0);
		bool let = (OldKey[input] == 1 && NowKey[input] == 0);
		return let;
	}
};