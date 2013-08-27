#ifndef __LINEDRAW_H__
#define __LINEDRAW_H__

#include "cocos2d.h"
#include "GraphHandle.h"

USING_NS_CC;
using namespace std;

class LineDraw :public CCNode{

public:
	virtual void draw();
	CC_SYNTHESIZE(CCPoint, _fixPoint, FixPoint);
	CC_SYNTHESIZE(CCPoint, _movedPoint, MovedPoint);
	CC_SYNTHESIZE(vector<CCPoint>, _beginPoint, BeginPoint);
	CC_SYNTHESIZE(vector<CCPoint>, _endPoint, EndPoint);
	CC_SYNTHESIZE(GraphHandle*, _graphHandle, GraphHandle)
	CC_SYNTHESIZE(vector<CCPoint>, arrayPoint, ArrayPoint);
	CC_SYNTHESIZE(int, beginIndex, BeginIndex);
	CC_SYNTHESIZE(int, oldBeginIndex, OldBeginIndex);

	virtual bool init();
	//static LineDraw* create();
	CREATE_FUNC(LineDraw);
// 	bool isOriginalPath(int, int);
// 	bool isDrawed(int, int);
// private:
// 	GraphHandle* handle; 
};






#endif __LINEDRAW_H__