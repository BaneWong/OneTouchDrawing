#ifndef __LINEPATH_H__
#define __LINEPATH_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define POINT_RADIUS 10

class LinePath :public CCNode{

public:
	virtual void draw();
	virtual bool init();
	CREATE_FUNC(LinePath);

	CC_SYNTHESIZE(vector<CCPoint>,arrayDraw,ArrayDraw);
	CC_SYNTHESIZE(int, ptCnt, PtCnt);
	CC_SYNTHESIZE(vector<vector<int>>, arrayConnect, ArrayConnect);

	bool containsPoint(int, int);

};






#endif __LINEPATH_H__