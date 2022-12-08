#pragma once

#include"DxLib.h"
#include"Charabase.h"
#include"player.h"

class Enemy : public CharaBase, public SphereColider
{
private:
	int hp;
	int maxhp;
	int point;

	//�v���C���[�̍��W
	int PlayerX;
	int PlayerY;

	//�U���̑ҋ@���ԂȂ�
	int Time;

public:
	Enemy(Location loc, float rad);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit() override;
	//virtual void Hit(int damage);
	void Hit(int damage);				//��e��
	//void HitPlayer(int BulletCnt);
	bool Checkhp();
	int Getpoint();
	void DeleteBullet(int bulletCnt);	//�e������

	void GetPlayerStat(Player* player);	//�v���C���[���擾

	void SircleShot(int way, int spd, int angle);	//�~�`�V���b�g(way���A�e���A�p�x)
	void HomingShot(int spd);						//���@�_��(�e��)
};