#ifndef _SELECTLEVEL_H_
#define _SELECTLEVEL_H_

#include "cocos2d.h"

USING_NS_CC;

class SelectLevel :public CCLayer{
public:
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(SelectLevel);
private:
	CCSize window_size; //´°¿Ú´óÐ¡
	CCLayer* getContainLayer();
};




#endif _SELECTLEVEL_H_