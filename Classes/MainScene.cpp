#include "MainScene.h"
#include "GameScene.h"
#include "SelectLevel.h"

CCScene* MainScene::scene(){

	CCScene* scene = CCScene::create();
	MainScene* layer = MainScene::create();
	scene->addChild(layer);
	return scene;

}

bool MainScene::init(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//使用创建的xml文件，取得定义的汉字  
	CCDictionary *strings = CCDictionary::createWithContentsOfFile("strings.xml");  
	const char *chinese = ((CCString*)strings->objectForKey("chinese"))->m_sString.c_str();

	CCLabelTTF *pLable = CCLabelTTF::create(chinese, "Marker Felt", 30);
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(pLable, this, menu_selector(MainScene::startCallback));
	CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
	pMenu->setPosition( ccp(winSize.width/2, winSize.height/2) );
	this->addChild(pMenu);
	return true;
}

void MainScene::startCallback(CCObject* pSender){
	CCScene* newScene = CCScene::create();
	newScene->addChild(SelectLevel::scene());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene));
}

char* MainScene::FontToUTF8(const char* font)
{
	int len=MultiByteToWideChar(CP_ACP,0,font,-1,NULL,0);
	wchar_t* wstr=new wchar_t[len+1];
	memset(wstr,0,len+1);
	MultiByteToWideChar(CP_ACP,0,font,-1,wstr,len);
	len=WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
	char* str=new char[len+1];
	memset(str,0,len+1);
	WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
	if(wstr)delete[] wstr;
	return str;
}