#pragma once

#include"DxLib.h"
#include"Charabase.h"
#include"player.h"

struct Moveinfo {
int pattern;	//�s���p�^�[��
Location Point;	//�ړI�n
int nextPointnum;	//���̔z��ԍ�
int Waittime;	//�҂�����
int  attack;	//�U���̎��
};

class Enemy : public CharaBase, public SphereColider
{
private:
	int hp;
	int maxhp;
	int point;

	int shotnum;

	//�v���C���[�̍��W
	int PlayerX;
	int PlayerY;

	//�U���̑ҋ@���ԂȂ�
	int Time;

	//�U���p�^�[��
	Moveinfo moveinfo[9];
	int current;
	int waittime;

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

	//�U���p�^�[���ǂݍ���
	void inputCSV();

	void Move();

	void GetPlayerStat(Player* player);	//�v���C���[���擾

	void SircleShot(Location loc, int way, int spd, float angle);	//�~�`�V���b�g(way���A�e���A�p�x)

	//�~�`���˃V���b�g(way���A�e���A�p�x�A�e�����̕ǂŔ��˂��邩(���ꂼ���A�E�A���A������))
	void SirclerefShot(Location loc, int way, int spd, float angle, bool up, bool right, bool down, bool left);

	void HomingShot(Location loc, int spd);						//���@�_��(�e��)

	 //��x�~�܂�V���b�g(�e���A���߂̑��x�A�~�܂�܂ł̎��ԁA�ҋ@���ԁA���̑��x,���̒e��)
	void StopShot(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd);

	//��x�~�܂�~�`�V���b�g(�e���Away���A�F�A���߂̑��x�A�~�܂�܂ł̎��ԁA�ҋ@���ԁA���̊p�x�A���̒e���AReang��way���ɉ����ĕω������邩)
	void SircleStopShot(Location loc, int way, int Stspd, float Stang, int stop, int time, int Reang, int Respd, bool ChangeReang);
};