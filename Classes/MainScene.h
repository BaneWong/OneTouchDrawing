#ifndef MAINSCENE_H_
#define MAINSCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class MainScene: public CCLayer{
public:
	virtual bool init();
	static CCScene* scene();
	void startCallback(CCObject* pSender);
	CREATE_FUNC(MainScene);
};
#endif MAINSCENE_H_