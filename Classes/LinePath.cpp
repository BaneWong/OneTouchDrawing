#include "LinePath.h"

bool LinePath::init()
{
// 	_fixPoint = CCPointZero;
// 	_movedPoint = CCPointZero;
	return true;
}

void LinePath::draw()
{
	// green
	glLineWidth( 1.0f );
	ccDrawColor4B(0,255,0,128);
	// �������г�ʶ·��
	for (int i = 0; i < ptCnt; i++)
		for (int j = 0; j <ptCnt; j++)
			if (i != j && containsPoint(j, i))//&& p[i] contains j
			{
				ccDrawLine(arrayDraw[i],arrayDraw[j]);
			}	
	// blue
	glLineWidth( 1.0f );
	ccDrawColor4B(0,0,255,128);
	// Ϊÿ���������һ��Ȧ
	for (int i = 0; i< arrayDraw.size(); i++)
		ccDrawCircle( arrayDraw[i], POINT_RADIUS, 0, 10, false);
}
// �ж�ĳ�����ǲ��������õ������յ㼯����
bool LinePath::containsPoint(int j, int i)
{
	for (int cnt = 0; cnt < arrayConnect[i].size(); cnt++) {	// a[] = [[2,3,4],[],[]] 
		if (j == arrayConnect[i][cnt])
			return true;
	}
	return false;
}