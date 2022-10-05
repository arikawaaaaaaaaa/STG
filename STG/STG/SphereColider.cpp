#include"SphereColider.h"
#include<math.h>

bool SphereColider::HitSphere(SphereColider hit) {

	//X,Y間の距離を取る
	Location location = hit.GetLocation();
	float x = location.X - this->location.X;
	float y = location.Y - this->location.Y;

	//絶対値を取る
	x = x < 0 ? -x : x;
	y = y < 0 ? -y : y;

	//ベクトルの大きさを取る
	float x2 = x * x;
	float y2 = y * y;
	float xy = x2 + y2;
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