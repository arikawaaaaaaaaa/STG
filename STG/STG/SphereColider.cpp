#include"SphereColider.h"
#include<math.h>

SphereColider::SphereColider(Location loc, float rad) {
	this->location.X = loc.X;
	this->location.Y = loc.Y;

	this->radius = rad;
}

bool SphereColider::HitSphere(SphereColider hit) {

	//X,Y間の距離を取る
	Location location = hit.GetLocation();
	float x = location.X - this->location.X;
	float y = location.Y - this->location.Y;

	//絶対値を取る
	x = fabsf(x);
	y = fabsf(y);

	//ベクトルの大きさを取る
	float xy = (x * x) + (y * y);
	double vecSize = sqrt(xy);

	//自分と相手の半径の和と比べる
	float rad = this->radius + hit.radius;

	//radより小さい?
	bool ret = (vecSize <= rad);
	return ret;
}

Location SphereColider::GetLocation() {
	return location;
}

void SphereColider::SetLocation(Location loc) {
	location.X = loc.X;
	location.Y = loc.Y;
}