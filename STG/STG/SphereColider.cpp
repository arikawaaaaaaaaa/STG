#include"SphereColider.h"
#include<math.h>

SphereColider::SphereColider(Location loc, float rad) {
	this->location.X = loc.X;
	this->location.Y = loc.Y;

	this->radius = rad;
}

bool SphereColider::HitSphere(SphereColider hit) {

	//X,Y�Ԃ̋��������
	Location location = hit.GetLocation();
	float x = location.X - this->location.X;
	float y = location.Y - this->location.Y;

	//��Βl�����
	x = fabsf(x);
	y = fabsf(y);

	//�x�N�g���̑傫�������
	float xy = (x * x) + (y * y);
	double vecSize = sqrt(xy);

	//�����Ƒ���̔��a�̘a�Ɣ�ׂ�
	float rad = this->radius + hit.radius;

	//rad��菬����?
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