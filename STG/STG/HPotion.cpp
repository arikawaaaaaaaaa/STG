#include "HPotion.h"
#include "common.h"
#include"DxLib.h"

HPotion::HPotion(Location loc)
	: ItemBase(loc, 10.f, E_ITEMTYPE::HPotion, Location{ 0,0.5f }), HealP(3)
{
	image = LoadGraph("images/Heart.png");
}

void HPotion::Update() {
	Location NewLoc = GetLocation();
	NewLoc.Y += speed.Y;
	SetLocation(NewLoc);
}

void HPotion::Draw() {
	DrawRotaGraph(GetLocation().X, GetLocation().Y, 1, 0, image, true, false, false);
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