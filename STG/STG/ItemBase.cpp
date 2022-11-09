#include "ItemBase.h"

ItemBase::ItemBase(Location location, float rad, E_ITEMTYPE type, Location spd)
    : SphereColider(location, rad), type(type), speed(spd)
{
    
}

void ItemBase::Update() {}
void ItemBase::Draw() {}
//E_ITEMTYPE GetType() { return type; }