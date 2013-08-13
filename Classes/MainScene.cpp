#include "MainScene.h"
#include "GameScene.h"

CCScene* MainScene::scene(){

	CCScene* scene = CCScene::create();
	MainScene* layer = MainScene::create();
	scene->addChild(layer);
	return scene;

}

bool MainScene::init(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::create("¿ªÊ¼", "Droid Sans Fallback", 56);
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(MainScene::startCallback));
	CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
	pMenu->setPosition( ccp(winSize.width/2, winSize.height/2.1) );
	this->addChild(pMenu);
	return true;
}

void MainScene::startCallback(CCObject* pSender){
	CCScene* newScene = CCScene::create();
	newScene->addChild(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene));
}