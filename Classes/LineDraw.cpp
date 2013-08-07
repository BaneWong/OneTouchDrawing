#include "LineDraw.h"

bool LineDraw::init()
{
 	_fixPoint = CCPointZero;
 	_movedPoint = CCPointZero;
	oldBeginIndex = beginIndex = -1;
	return true;
}

void LineDraw::draw()
{
	glLineWidth( 5.0f );
	// red
	ccDrawColor4B(255,0,0,128);
	// ��������������ɵ��߶��Ѿ������򲻻�
	// ������������ɵ��߶β���ԭ·����Χ���򲻻�
	// ����ƶ��ĵ㲻������һ��Ȧ��Χ��,��

	// �������ߣ�
	ccDrawLine(_fixPoint, _movedPoint);

	//if(isOriginalPath(oldBeginIndex, beginIndex) && !(isDrawed(oldBeginIndex, beginIndex)))
		

}

// �ж������߶��Ƿ���ԭ·����Χ��
bool LineDraw::isOriginalPath(int start, int end)
{
	// ��Ϊ������� ����ֻ���ж�һ��
	if((start != end) && start > 0 && end > 0)
	{
		EdgeNode* find = _graphHandle->agl.adList[start].firstAdNode;
		while (find != NULL)
		{
			if(find->index == end)
				return true;
		}
	}
	return false;
}

// �ж������߶��Ƿ��Ѿ�����
bool LineDraw::isDrawed(int start, int end)
{
	if((start != end) && start > 0 && end > 0)
	{
		// ����ͼ�����������߶��Ƿ��Ѿ�����
		EdgeNode* find = _graphHandle->agl.adList[start].firstAdNode;
		while (find != NULL)
		{
			if(find->IsDrawed == true)
				return true;
		}
		return false;
	}
	
}