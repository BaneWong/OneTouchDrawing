#ifndef _SELECTLEVEL_H_
#define _SELECTLEVEL_H_

#include "LsTouch.h"

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SelectLevel :public CCLayer, LsTouchEvent{
public:
    
    SelectLevel();
    ~SelectLevel();
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(SelectLevel);
    
    virtual void touchEventAction(LsTouch* touch, int type);

    
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

    
    CCLayer* getContainLayer();
    CCNode* createSpriteByLevel(int level);
    void adjustScrollView(float offset);
    void loadUserData();

private:
	CCSize window_size; 
    CCLayer* layer;
    
    CCPoint m_touchPoint;
    CCPoint m_touchOffset;
    
    int m_nCurPage;
    int m_nPageCount;
    CC_SYNTHESIZE_RETAIN(CCScrollView*, m_pScrollView, ScrollView);
	CC_SYNTHESIZE(int, m_nLevelNumber, LevelNumber);
};




#endif _SELECTLEVEL_H_