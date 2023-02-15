#include "HPotion.h"
#include "common.h"
#include"DxLib.h"

HPotion::HPotion(Location loc)
	: ItemBase(loc, 5.f, E_ITEMTYPE::HPotion, Location{ 0,0.5f }), HealP(3)
{

}

void HPotion::Update() {
	Location NewLoc = GetLocation();
	NewLoc.Y += speed.Y;
	SetLocation(NewLoc);
}

void HPotion::Draw() {
	DrawCircle(GetLocation().X, GetLocation().Y, GetRadius(), 0xffffff);
}

bool HPotion::IsDeath() {
	float x = GetLocation().X + GetRadius();
	float y = GetLocation().Y + GetRadius();

	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;

	int margin = 20;
	if (y < 0 - margin || y > height + margin || x < 0 || x > width) {
		return true;
	}
	return false;
}