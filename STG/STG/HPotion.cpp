#include "HPotion.h"
#include"DxLib.h"

HPotion::HPotion(Location loc)
	: ItemBase(loc, 5.f, E_ITEMTYPE::NORMAL, Location{ 0,0.5f }), HealP(3)
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