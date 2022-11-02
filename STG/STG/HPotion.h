#pragma once
#include "ItemBase.h"
class HPotion :
    public ItemBase
{
private:
    int HealP;

public:
    HPotion(Location loc);

public:

    virtual void Update();
    virtual void Draw();
};

