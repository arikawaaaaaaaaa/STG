#include"player.h"
#include"dxlib.h"
#include"KeyMng.h"
#include"straightBlt.h"
#include"HPotion.h"
#include"common.h"

Location GetNewLocation(Location NewLoc);

Player::Player(Location loc, float rad) :SphereColider(loc, rad) {
	Score = 0;
	Life = 10;
	MaxLife = Life;

	HitCool = 0;
	ShotCool = 0;

	image = LoadGraph("images/player.png");
	LoadDivGraph("images/bullet_b.png", 8, 8, 1, 16, 16, bullet);

	bullets = new BulletsBase*[BltLimit];
	for (int i = 0; i < BltLimit; i++) {
		bullets[i] = nullptr;
	}
}

void Player::Update() {

	Location NewLoc = GetNewLocation(GetLocation());
	SetLocation(NewLoc);

	int bulletcount;
	for (bulletcount = 0; bulletcount < BltLimit; bulletcount++) {

		if (bullets[bulletcount] == nullptr) { break; }
		
		bullets[bulletcount]->Update();

		if (bullets[bulletcount]->isDeath()) {	//�e����ʊO�ɏo���H
			
			delete bullets[bulletcount];		//�o���e������
			bullets[bulletcount] = nullptr;

			for (int i = bulletcount + 1; i < BltLimit; i++) {	//�e�̔z��ɂł����󔒂𖄂߂�

				if (bullets[i] == nullptr) { break; }

				bullets[i - 1] = bullets[i];
				bullets[i] = nullptr;
			}
			bulletcount--;
		}
	}

	if (KeyMng::OnPress(KEY_INPUT_Z) && ShotCool <= 0) {	//�e�𔭎˂���
		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {	//��ʏ�̒e�̐��͍ő�l�����H
			bullets[bulletcount] = new straightBlt({ GetLocation().X,GetLocation().Y-48 }, 7, 0.f, 7, bullet);	//�^�Ȃ�e�𔭎˂���
			ShotCool = 4;
		}
	}

	if (MaxLife * 2 < Life)Life = MaxLife * 2;
	if (0 < HitCool)HitCool--;
	if (0 < ShotCool)ShotCool--;
}

void Player::Draw() {

	//�v���C���[�摜
	DrawRotaGraph((int)GetLocation().X, (int)GetLocation().Y-16, 1, 0, image, true, false, false);

	//shift�����Ă�Ȃ瓖���蔻���\��
	if (KeyMng::OnPress(KEY_INPUT_LSHIFT)) {
		DrawCircle((int)GetLocation().X, (int)GetLocation().Y, (int)GetRadius(), 0xff0000);
	}

	//�e�\��
	for (int i = 0; i < BltLimit; i++) {
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}
}

void Player::Hit() {

	if (!HitCool) {
		Life--;
		HitCool = 30;	//��_���[�W�Ɣ�e�㖳�G���Ԑݒ�
	}
	if (Life < 0)Life = 0;
}

void Player::Hit(int BulletCnt) {
	delete bullets[BulletCnt];
	bullets[BulletCnt] = nullptr;

	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//�e�̔z��ɂł����󔒂𖄂߂�

		if (bullets[i] == nullptr) { break; }

		bullets[i - 1] = bullets[i];
		bullets[i] = nullptr;
	}
}

void Player::Hit(class ItemBase* item) {
	
	E_ITEMTYPE type = item->GetType();

	switch (type)
	{
	case E_ITEMTYPE::HPotion:
	{HPotion* potion = dynamic_cast<HPotion*>(item);
	if (potion == nullptr)throw - 1;

	this->Life += potion->GetHealP();

	break;
	}
	default:
		break;
	}
}

bool Player::LifeCheck() {
	bool ret = (Life <= 0);
	return ret;
}

int Player::GetScore() { return Score; }

Location GetNewLocation(Location NewLoc) {
	
	//�X�s�[�h�ݒ�
	float spd = 3.0;

	//shift��������Ă���ƌ���
	if (KeyMng::OnPress(KEY_INPUT_LSHIFT))spd = 1;

	//�E�ړ�
	if (KeyMng::OnPress(KEY_INPUT_RIGHT)) {
		NewLoc.X += spd;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X -= 1.5f;
	}

	//���ړ�
	if (KeyMng::OnPress(KEY_INPUT_LEFT)) {
		NewLoc.X -= spd;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X += 1.5f;
	}

	//��ړ�
	if (KeyMng::OnPress(KEY_INPUT_UP)) {
		NewLoc.Y -= spd;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y += 1.5f;
	}

	//���ړ�
	if (KeyMng::OnPress(KEY_INPUT_DOWN)) {
		NewLoc.Y += spd;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y -= 1.5f;
	}

	//��ʊO�ɏo�Ȃ��悤�ɂ���
	if (NewLoc.X < SCREEN_MARGIN)NewLoc.X = SCREEN_MARGIN;
	if (NewLoc.Y < 0)NewLoc.Y = 0.0;
	if (NewLoc.X > SCREEN_WIDTH - SCREEN_MARGIN)NewLoc.X = SCREEN_WIDTH - SCREEN_MARGIN;
	if (NewLoc.Y > 720)NewLoc.Y = 720.0;

	return NewLoc;
}