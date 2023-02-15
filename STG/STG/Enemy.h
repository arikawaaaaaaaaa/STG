#pragma once

#include"DxLib.h"
#include"Charabase.h"
#include"player.h"

struct Moveinfo {
int pattern;	//�s���p�^�[��
Location Point;	//�ړI�n
Location Speed;	//�X�s�[�h
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

	int phase;	//�i�s�x

	//�v���C���[�̍��W
	int PlayerX;
	int PlayerY;

	//�U���̑ҋ@���ԂȂ�
	int Time;
	int angle;

	int bullet_A[8];
	int bullet_B[8];
	int bullet_C[8];

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

	Location GetLoc() { return GetLocation(); }
	int GetLife() { return hp; }

	//�U���p�^�[���ǂݍ���
	void inputCSV();

	void Move();

	void GetPlayerStat(Player* player);	//�v���C���[���擾

	void SircleShot(Location loc, int way, float spd, float angle, int col);	//�~�`�V���b�g(way���A�e���A�p�x�A�F)

	//�~�`���˃V���b�g(way���A�e���A�p�x�A�e�����̕ǂŔ��˂��邩(���ꂼ���A�E�A���A������)�A�F)
	void SirclerefShot(Location loc, int way, int spd, float angle, bool up, bool right, bool down, bool left, int col);

	void HomingShot(Location loc, float spd, int ang, int col);						//���@�_��(�e���A���炵�A�F)

	 //��x�~�܂�V���b�g(�e���A���߂̑��x�A�~�܂�܂ł̎��ԁA�ҋ@���ԁA���̑��x,���̒e��)
	void StopShot(Location loc, int Stspd, float Stang, int stop, int time, int Reang, int Respd, int col);

	//��x�~�܂�~�`�V���b�g(way���A���߂̑��x�A���߂̊p�x�A�~�܂�܂ł̎��ԁA�ҋ@���ԁA���̊p�x�A���̒e���AReang��way���ɉ����ĕω������邩�A�F)
	void SircleStopShot(Location loc, int way, int Stspd, float Stang, int stop, int time, int Reang, int Respd, bool ChangeReang, int col);
};