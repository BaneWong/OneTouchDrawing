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
	// 如果这两个点连成的线段已经有了则不画
	// 如果两个点连成的线段不在原路径范围内则不画
	// 如果移动的点不在任意一个圈范围内,则画

	// 画动的线：
	ccDrawLine(_fixPoint, _movedPoint);

	//if(isOriginalPath(oldBeginIndex, beginIndex) && !(isDrawed(oldBeginIndex, beginIndex)))
		

}

// 判断这条线段是否在原路径范围内
bool LineDraw::isOriginalPath(int start, int end)
{
	// 因为是无向的 所以只需判断一边
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

// 判断这条线段是否已经画过
bool LineDraw::isDrawed(int start, int end)
{
	if((start != end) && start > 0 && end > 0)
	{
		// 遍历图，查找这条线段是否已经画过
		EdgeNode* find = _graphHandle->agl.adList[start].firstAdNode;
		while (find != NULL)
		{
			if(find->IsDrawed == true)
				return true;
		}
		return false;
	}
	
}