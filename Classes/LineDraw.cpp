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
	// �߿�
	glLineWidth( 5.0f );
	// red
	ccDrawColor4B(255,0,0,128);	

	// �������ߣ�
	ccDrawLine(_fixPoint, _movedPoint);

	
	// �����Ѿ��������
	for(int i = 0;i < arrayPoint.size();i++)
	{
		EdgeNode* find = _graphHandle->agl.adList[i].firstAdNode;
		while(find != NULL)
		{
			if(find->IsDrawed == true)			
				ccDrawLine(arrayPoint[i], arrayPoint[find->index]);			
			find = find->next;
		}	
	}
}

