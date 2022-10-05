#pragma once
struct Location 
{
	float X;
	float Y;
};

class SphereColider {
private:
	Location location;
	float radius;

public:
	bool HitSphere(SphereColider hit);
	Location GetLocation();
	void SetLocation(Location loc);
};