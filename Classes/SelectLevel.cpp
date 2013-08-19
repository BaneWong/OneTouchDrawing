#include "SelectLevel.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

static int world_cnt = 3; //大关卡数数
static int level_cnt = 48; //每个世界的小关卡数
static int width_cnt = 4; //横向显示的小关卡数
static int height_cnt = 4; //纵向显示的小关卡数

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
	CCScrollView* scroll_view = CCScrollView::create(CCSizeMake(640, 1136));
	//CCScrollView* scroll_view = CCScrollView::create(this->getContentSize());
	scroll_view->setContainer(getContainLayer());
	scroll_view->setTouchEnabled(false);
	this->addChild(scroll_view);
	this->setTouchEnabled(true);

	return true;
}

CCLayer* SelectLevel::getContainLayer(){
	CCLayer* layer = CCLayer::create();
	layer->setPosition(CCPointZero);

	CCPoint point_center = ccp(window_size.width / 2, window_size.height / 2);
	float x_world_offset = window_size.width / 5;
	float y_world_offset = window_size.height / 5;

	for(int i = 0; i < world_cnt; i++){
		CCSprite* world = CCSprite::create("world-iphone5.jpg");
		//world->setScale(0.5);
		world->setPosition(ccpAdd(point_center,ccp(window_size.width * (i % world_cnt), 0)));
		layer->addChild(world, 0);
	}
	
	float x_level_offset = (window_size.width - width_cnt * 100 - (width_cnt - 1) * 50) / 2;
	float y_level_offset = window_size.height * 4/5;
		
	for(int i = 0; i < level_cnt; i++){
		int current_page_index = i / (width_cnt * height_cnt);
		CCSprite* level = CCSprite::create("level-iphone5.jpg");
		//level->setScale(0.5);
		level->setAnchorPoint(CCPointZero);
		level->setPosition(ccp((x_level_offset + (i % width_cnt) * (100 + 50) + current_page_index * window_size.width),
							   (y_level_offset - (i % (width_cnt * height_cnt) / height_cnt) * (100 + 50))));
		layer->addChild(level, 2);
	}
	layer->setContentSize(CCSizeMake(window_size.width * world_cnt, window_size.height));
	return layer;
}