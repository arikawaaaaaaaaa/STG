#pragma once
#include "ItemBase.h"
class HPotion :
    public ItemBase
{
private:
    int HealP;
    int image;

public:
    HPotion(Location loc);

public:

    virtual void Update();
    virtual void Draw();

    bool IsDeath();

    int GetHealP() { return HealP; }
};

