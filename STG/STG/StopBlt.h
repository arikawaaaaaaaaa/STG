#pragma once
#include "BulletsBase.h"

class StopBlt : public BulletsBase	//��x�~�܂��ĕ����]������e
{
private:
	int image;

	int spd;			//�e��
	Location StSpd;	//�������x
	int Respd;		//�����]����̑��x
	int Reang;		//���@�]����̊p�x
	int time;		//�o�ߎ���
	int StopTime;	//�~�܂�܂ł̎���(flame)
	int WaitTime;	//�~�܂��Ă��瓮���o���܂ł̎���(flame)

public:
	StopBlt(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd);	//�R���X�g���N�^

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isDeath() override;
};

