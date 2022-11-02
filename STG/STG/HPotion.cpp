#include "HPotion.h"

HPotion::HPotion(Location loc)
	: ItemBase(loc, 5.f, E_ITEMTYPE::NORMAL, Location{ 0,0.5f }), HealP(3)
{

}

void HPotion::Update() {}
void HPotion::Draw() {}