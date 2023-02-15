#pragma once
#include "SphereColider.h"
enum class E_ITEMTYPE {
    HPotion=0

};

class ItemBase :
    public SphereColider
{
protected:
    E_ITEMTYPE type;
    Location speed;

public:
    ItemBase(Location location, float rad, E_ITEMTYPE type, Location spd);

public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool IsDeath() = 0;
    E_ITEMTYPE GetType() { return type; }

};

