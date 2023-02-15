#include"player.h"
#include"dxlib.h"
#include"KeyMng.h"
#include"straightBlt.h"
#include"HPotion.h"
#include"common.h"

#define DEBUG

Location GetNewLocation(Location NewLoc);

Player::Player(Location loc, float rad) :SphereColider(loc, rad) {
	Score = 0;
	Life = 999;

	ShotCool = 0;

	LoadDivGraph("images/bullet_c.png", 8, 8, 1, 14, 16, bullet);

	//image‰Šú‰»
	//speed‰Šú‰»

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

		if (bullets[bulletcount]->isDeath()) {	//’e‚ª‰æ–ÊŠO‚Éo‚½H
			
			delete bullets[bulletcount];		//o‚½’e‚ğÁ‚·
			bullets[bulletcount] = nullptr;

			for (int i = bulletcount + 1; i < BltLimit; i++) {	//’e‚Ì”z—ñ‚É‚Å‚«‚½‹ó”’‚ğ–„‚ß‚é

				if (bullets[i] == nullptr) { break; }

				bullets[i - 1] = bullets[i];
				bullets[i] = nullptr;
			}
			bulletcount--;
		}
	}

	if (KeyMng::OnPress(KEY_INPUT_Z) && ShotCool <= 0) {	//’e‚ğ”­Ë‚·‚é
		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {	//‰æ–Êã‚Ì’e‚Ì”‚ÍÅ‘å’l–¢–H
			bullets[bulletcount] = new straightBlt(GetLocation(), 7, 0.f, 7, bullet);	//^‚È‚ç’e‚ğ”­Ë‚·‚é
			ShotCool = 4;
		}
	}

	if (0 < ShotCool)ShotCool--;
}

void Player::Draw() {
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, (int)GetRadius(), 0xff0000);

	for (int i = 0; i < BltLimit; i++) {
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}

#ifdef DEBUG

	DrawFormatString(10, 10, 0xffffff, "Life : %d", this->Life);
#endif // DEBUG


}

void Player::Hit() {
	if (--Life < 0)Life = 0;
}

void Player::Hit(int BulletCnt) {
	delete bullets[BulletCnt];
	bullets[BulletCnt] = nullptr;

	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//’e‚Ì”z—ñ‚É‚Å‚«‚½‹ó”’‚ğ–„‚ß‚é

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
	
	float spd = 3.0;
	if (KeyMng::OnPress(KEY_INPUT_LSHIFT))spd = 1.5;

	if (KeyMng::OnPress(KEY_INPUT_RIGHT)) {
		NewLoc.X += spd;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X -= 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_LEFT)) {
		NewLoc.X -= spd;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X += 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_UP)) {
		NewLoc.Y -= spd;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y += 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_DOWN)) {
		NewLoc.Y += spd;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y -= 1.5f;
	}

	if (NewLoc.X < SCREEN_MARGIN)NewLoc.X = SCREEN_MARGIN;
	if (NewLoc.Y < 0)NewLoc.Y = 0.0;
	if (NewLoc.X > SCREEN_WIDTH - SCREEN_MARGIN)NewLoc.X = SCREEN_WIDTH - SCREEN_MARGIN;
	if (NewLoc.Y > 720)NewLoc.Y = 720.0;

	return NewLoc;
}