//2013-08-19 21:59:38
#include "SelectLevel.h"
#include "LsTouch.h"
#include "GameScene.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

static int world_cnt = 3; // world number
static int level_cnt = 48; // level number
static int width_cnt = 4; // the display count per line per page
static int height_cnt = 4; // the display count per colum per page
static int TAG_DISPLAY = 1000;


SelectLevel::SelectLevel():m_nCurPage(0),m_nPageCount(0)
{

}

SelectLevel::~SelectLevel()
{

}

CCScene* SelectLevel::scene(){
	CCScene* scene = CCScene::create();
	SelectLevel* layer = SelectLevel::create();
	scene->addChild(layer);
	return scene;
}

bool SelectLevel::init(){
	window_size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* background = CCSprite::create("background-iphone5.jpg");
	//background->setScale(0.5);
	background->setPosition(ccp(window_size.width/2, window_size.height/2));
	this->addChild(background);

	// add scrollview
	m_pScrollView = CCScrollView::create(CCSizeMake(640, 1136));
	//CCScrollView* scroll_view = CCScrollView::create(this->getContentSize());
	m_pScrollView->setContainer(getContainLayer());
	m_pScrollView->setTouchEnabled(false);
    setScrollView(m_pScrollView);

    this->addChild(m_pScrollView);
    this->setTouchEnabled(true);


    return true;
}

CCLayer* SelectLevel::getContainLayer(){
	layer = CCLayer::create();
	layer->setPosition(CCPointZero);

	CCPoint point_center = ccp(window_size.width / 2, window_size.height / 2);

    m_nPageCount = (level_cnt - 1) / (width_cnt * height_cnt) + 1;
    
    for(int i = 0; i < m_nPageCount; i++){
      CCSprite* world = CCSprite::create("world-iphone5.jpg");
      world->setPosition(ccpAdd(point_center,ccp(window_size.width * (i % world_cnt), 0)));
      layer->addChild(world, 0);
  }
	// set the distance 50;the picture is 100x100
    // TODO: change the hard code:100
  float x_level_offset = (window_size.width - width_cnt * 100 - (width_cnt - 1) * 50) / 2;
  float y_level_offset = window_size.height * 4/5;

  CCSprite* sprite = CCSprite::create("level-iphone5.jpg");
  sprite->setAnchorPoint(CCPointZero);
  sprite->setPosition(ccp(45, 0));
  layer->addChild(sprite);

  for(int i = 0; i < level_cnt; i++){
      int current_page_index = i / (width_cnt * height_cnt);
		CCNode* level = createSpriteByLevel(i); // why wrong start x positioin
        //CCNode* level = CCSprite::create("level-iphone5.jpg"); // correct start x positioin
		level->setAnchorPoint(CCPointZero);
        // TODO: change the hard code
		level->setPosition(ccp((x_level_offset + (i % width_cnt) * (100 + 50) + current_page_index * window_size.width),
          (y_level_offset - (i % (width_cnt * height_cnt) / height_cnt) * (100 + 50))));
        // add tag for display
		layer->addChild(level, 2, i);
	}
	layer->setContentSize(CCSizeMake(window_size.width * m_nPageCount, window_size.height));
	return layer;
}

CCNode* SelectLevel::createSpriteByLevel(int level){
	CCSprite* sprite = CCSprite::create("level-iphone5.jpg");

//     CCMenuItemImage* pMenuItemImage = CCMenuItemImage::create("level-iphone5.jpg",
//                                                               "level-iphone5.jpg",
//                                                               this,
//                                                               menu_selector(SelectLevel::startGameCallback));
//     CCMenu* pImageMenu = CCMenu::create(pMenuItemImage);

	LsTouch* ls_touch = LsTouch::create();
	ls_touch->setDisplay(sprite);
	this->addLsTouch(ls_touch, level);
	return ls_touch;

}

void SelectLevel::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool SelectLevel::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    m_touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    m_touchOffset = getScrollView()->getContentOffset();
    sendTouchMessage(pTouch, 0);
    return true;
}

void SelectLevel::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    float distance = movePoint.x - m_touchPoint.x;
    // 设定当前偏移位置
    CCPoint adjustPoint = ccp(m_touchOffset.x + distance, 0);
    getScrollView()->setContentOffset(adjustPoint, false);
    //sendTouchMessage(pTouch, 1);
}

void SelectLevel::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    float distance = endPoint.x - m_touchPoint.x;
    float distanceY = endPoint.y - m_touchPoint.y;
    if (fabs(distance) < 3 && fabs(distanceY) < 3){
        // 小于三，不做拖动操作，也排除了（抖动误操作）,第二个参数，事件类型 1： touch end， 由 touchEventAction 自动相应
        sendTouchMessage(pTouch, 1);
        
    }else if (fabs(distance) > 50){
        // 大于 50，执行拖动效果
        adjustScrollView(distance);
        //setCurPageBall();
    }else{
        // 回退为拖动之前的位置
        adjustScrollView(0);
    }
    
    sendTouchMessage(pTouch, 2);
    // just for try,need to find another place to place this function
    loadUserData();
}

void SelectLevel::touchEventAction(LsTouch* touch, int type){
    // type 事件类型，0：touchbegin 1：touchend 触发 2：touchend 未触发
    if (touch)
        CCLog("touch event action id: %d  type: %d", touch->getEventId(), type);
    const int selectTag = 10001;
    if (type == 0 && touch){
        getScrollView()->getContainer()->removeChildByTag(selectTag);
        // 添加选撞状态的精灵，背景
        CCSprite* sprite = CCSprite::create("sel.png");
        sprite->setScaleX(2);
        sprite->setScaleY(4);
        sprite->setPosition(touch->getPosition());
        getScrollView()->getContainer()->addChild(sprite, 1, selectTag);
        
    } else {
        getScrollView()->getContainer()->removeChildByTag(selectTag);
    }
    if (type == 2 && touch){
        // 收到 type 为 1 表示触发关卡选择
		// pass the touch level number to GameScene		
      CCScene* newScene = CCScene::create();
        // eventId begin from 0,but the xml file begin from "path1.xml",so plus one
      int levelID = touch->getEventId() + 1;
      GameScene* game_scene = GameScene::create(levelID);
		// set the ID to be retrieved by the instance of GameScene
      newScene->addChild(game_scene);
      CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene));
  }
}

void SelectLevel::adjustScrollView(float offset){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    // 我们根据 offset 的实际情况来判断移动效果
    if (offset < 0)
        m_nCurPage ++;
    else if (offset > 0)
        m_nCurPage --;
    
    if (m_nCurPage < 0)
        m_nCurPage = 0;
    else if (m_nCurPage > m_nPageCount - 1)
        m_nCurPage = m_nPageCount - 1;
    
    CCPoint adjustPoint = ccp(-winSize.width * m_nCurPage , 0);
    getScrollView()->setContentOffsetInDuration(adjustPoint, 0.2f);
    
    CCLog("current page index: %d", m_nCurPage);
}
// add loadUserData every time replace SelectLevel scene
void SelectLevel::loadUserData(){
    float x_level_offset = (window_size.width - width_cnt * 100 - (width_cnt - 1) * 50) / 2;
    float y_level_offset = window_size.height * 4/5;
    for(int i = 0; i < 2; i++){
        int current_page_index = i / (width_cnt * height_cnt);

        std::ostringstream oss;
        int iPlusOne = i + 1;
        oss << iPlusOne;
        string strLevelID = oss.str();
 
        bool isAchieved = CCUserDefault::sharedUserDefault()->getBoolForKey(strLevelID.c_str());
        if(isAchieved){
            CCSprite* achieved = CCSprite::create("achieved-iphone5.png");
            achieved->setPosition(ccp((x_level_offset + (i % width_cnt) * (100 + 50) + current_page_index * window_size.width),
             (y_level_offset - (i % (width_cnt * height_cnt) / height_cnt) * (100 + 50))));           
            this->addChild(achieved);
        }


    }
}