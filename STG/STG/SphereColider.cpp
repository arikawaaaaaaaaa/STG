#include"SphereColider.h"
#include<math.h>

bool SphereColider::HitSphere(SphereColider hit) {

	//X,Y�Ԃ̋��������
	Location location = hit.GetLocation();
	float x = location.X - this->location.X;
	float y = location.Y - this->location.Y;

	//��Βl�����
	x = x < 0 ? -x : x;
	y = y < 0 ? -y : y;

	//�x�N�g���̑傫�������
	float x2 = x * x;
	float y2 = y * y;
	float xy = x2 + y2;
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