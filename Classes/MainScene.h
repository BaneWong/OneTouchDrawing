#ifndef MAINSCENE_H_
#define MAINSCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class MainScene: public CCLayer{
public:
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(MainScene);

	void startCallback(CCObject* pSender);
	//char* FontToUTF8(const char* font);
	
};
#endif MAINSCENE_H_