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
	Life = 5;

	//image初期化
	//speed初期化

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

		if (bullets[bulletcount]->isDeath()) {	//弾が画面外に出た？
			
			delete bullets[bulletcount];		//出た弾を消す
			bullets[bulletcount] = nullptr;

			for (int i = bulletcount + 1; i < BltLimit; i++) {	//弾の配列にできた空白を埋める

				if (bullets[i] == nullptr) { break; }

				bullets[i - 1] = bullets[i];
				bullets[i] = nullptr;
			}
			bulletcount--;
		}
	}

	if (KeyMng::OnClick(KEY_INPUT_Z)) {	//弾を発射する
		if (bullets[bulletcount] == nullptr && bulletcount < BltLimit) {	//画面上の弾の数は最大値未満？
			bullets[bulletcount] = new straightBlt(GetLocation(), 5, 0.f);	//真なら弾を発射する
		}
	}

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

	for (int i = BulletCnt + 1; i < BltLimit; i++) {	//弾の配列にできた空白を埋める

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