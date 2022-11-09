#include"player.h"
#include"dxlib.h"
#include"KeyMng.h"
#include"straightBlt.h"
#include"HPotion.h"

#define DEBUG

Location GetNewLocation(Location NewLoc);

Player::Player(Location loc, float rad) :SphereColider(loc, rad) {
	Score = 0;
	Life = 5;

	//image‰Šú‰»
	//speed‰Šú‰»

	bullets = new BulletsBase*[30];
	for (int i = 0; i < 30; i++) {
		bullets[i] = nullptr;
	}
}

void Player::Update() {

	Location NewLoc = GetNewLocation(GetLocation());
	SetLocation(NewLoc);

	int bulletcount;
	for (bulletcount = 0; bulletcount < 30; bulletcount++) {

		if (bullets[bulletcount] == nullptr) { break; }
		
		bullets[bulletcount]->Update();

		if (bullets[bulletcount]->isDeath()) {	//’e‚ª‰æ–ÊŠO‚Éo‚½H
			
			delete bullets[bulletcount];		//o‚½’e‚ğÁ‚·
			bullets[bulletcount] = nullptr;

			for (int i = bulletcount + 1; i < 30; i++) {	//’e‚Ì”z—ñ‚É‚Å‚«‚½‹ó”’‚ğ–„‚ß‚é

				if (bullets[i] == nullptr) { break; }

				bullets[i - 1] = bullets[i];
				bullets[i] = nullptr;
			}
			bulletcount--;
		}
	}

	if (KeyMng::OnClick(KEY_INPUT_Z)) {	//’e‚ğ”­Ë‚·‚é
		if (bullets[bulletcount] == nullptr && bulletcount < 30) {	//‰æ–Êã‚Ì’e‚Ì”‚ÍÅ‘å’l–¢–H
			bullets[bulletcount] = new straightBlt(GetLocation(), 5, 0.f);	//^‚È‚ç’e‚ğ”­Ë‚·‚é
		}
	}

}

void Player::Draw() {
	DrawCircle((int)GetLocation().X, (int)GetLocation().Y, (int)GetRadius(), 0xff0000);

	for (int i = 0; i < 30; i++) {
		if (bullets[i] == nullptr) { break; }
		bullets[i]->Draw();
	}

#ifdef DEBUG

	DrawFormatString(10, 10, 0xffffff, "Life : %d", this->Life);
#endif // DEBUG


}

void Player::Hit() {}

void Player::Hit(int BulletCnt) {
	delete bullets[BulletCnt];
	bullets[BulletCnt] = nullptr;

	for (int i = BulletCnt + 1; i < 30; i++) {	//’e‚Ì”z—ñ‚É‚Å‚«‚½‹ó”’‚ğ–„‚ß‚é

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
	
	if (KeyMng::OnPress(KEY_INPUT_RIGHT)) {
		NewLoc.X += 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X -= 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_LEFT)) {
		NewLoc.X -= 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_UP) || KeyMng::OnPress(KEY_INPUT_DOWN)) NewLoc.X += 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_UP)) {
		NewLoc.Y -= 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y += 1.5f;
	}
	if (KeyMng::OnPress(KEY_INPUT_DOWN)) {
		NewLoc.Y += 3.0f;
		//if (KeyMng::OnPress(KEY_INPUT_LEFT) || KeyMng::OnPress(KEY_INPUT_RIGHT)) NewLoc.Y -= 1.5f;
	}

	if (NewLoc.X < 0)NewLoc.X = 0.0;
	if (NewLoc.Y < 0)NewLoc.Y = 0.0;
	if (NewLoc.X > 1280)NewLoc.X = 1280.0;
	if (NewLoc.Y > 720)NewLoc.Y = 720.0;

	return NewLoc;
}