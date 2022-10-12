#include"Charabase.h"

CharaBase:: ~CharaBase() {
	if (image != nullptr) {
		delete[] image;
	}
}

Location CharaBase::GetSpeed() { return speed; }

void CharaBase::SetSpeed(Location speed) { 
	this->speed.X = speed.X;
	this->speed.Y = speed.Y;
}
