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
	// 线宽
	glLineWidth( 5.0f );
	// red
	ccDrawColor4B(255,0,0,128);	

	// 画动的线：
	ccDrawLine(_fixPoint, _movedPoint);

	
	// 绘制已经保存的线
	for(size_t i = 0;i < arrayPoint.size();i++)
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

