/* 
	TODO: judge the repeated lines,discard them(finished)
	TODO: add restart and back button
		  begin: 2013-8-21 10:58
		    end: 2013-8-27 10:04

	TODO: 2013-8-21 10:59 add the judgement of win or lose current level
		  begin: 2013-8-21 10:59
		    end: 2013-8-27 10:04

	TODO: translate all the comment to english
		  begin: 2013-8-21 10:59

	TODO: add the save module,to save the player pass how many levels
		  begin: 2013-8-21 11:17
*/
#include "GameScene.h"
#include "SelectLevel.h"

using namespace cocos2d;

GameScene::~GameScene(){
	parseXml->release();
	if(isInCircle)
		drawLine->release();
}

GameScene* GameScene::create(int levelID){
	GameScene* scene = new GameScene();
	if(scene && scene->init(levelID)){
		scene->autorelease();
		return scene;
	}
	CC_SAFE_RELEASE(scene);
	return NULL;
}

// on "init" you need to initialize your instance
bool GameScene::init(int levelID)
{
	beginIndex = -1;
	oldBeginIndex = -1;
	isInCircle = false;
	isStart = false;

	m_nLevelID = levelID;

	createRestartAndBackMenu();
	createOriginalPath();
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	// �Զ������ڷ�Χ�ڵĵ�����Ϊ������
//  	if(isInCircle)
//  	{
//  		drawLine->setFixPoint(arrayPointDraw[beginIndex]);
//  		//drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
//  	}
}

void GameScene::restartCallback(CCObject* pSender){
	drawLine->release();
}


void GameScene::returnCallback(CCObject* pSender){
	CCScene* scene = CCScene::create();
	SelectLevel* layer = SelectLevel::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(0.4f, scene));
}

void GameScene::createRestartAndBackMenu(){
	CCMenuItem* item2 = CCMenuItemImage::create("back-iphone5.png", "back-iphone5.png", this, menu_selector(GameScene::returnCallback) );
	CCMenu* resartMenu = CCMenu::create(item2, NULL);
	resartMenu->setPosition(ccp(50, 1100));
	this->addChild(resartMenu);
}

void GameScene::createOriginalPath()
{	
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	// ���������ļ� ��ʼ���ؿ�	
	// convert int to string
	std::ostringstream oss;
	oss << m_nLevelID;
	string parase_file = "path" + oss.str() + ".xml";
	parseXml = HXmlParse::parserWithFile(parase_file.c_str());//xml�ļ�
	// need to use in below functions
	parseXml->retain();

	pointCnt = parseXml->arrayPoint.size();
	for (int i = 0; i < pointCnt; i++)
		arrayPointDraw.push_back(parseXml->arrayPoint[i]);

	// �������е�ÿ�������ӵĵ㼯����ȡ����
	arrayConnectTo = parseXml->arrayConnect;

	
	path = LinePath::create();
	path->setArrayDraw(arrayPointDraw);
	path->setPtCnt(pointCnt);
	path->setArrayConnect(arrayConnectTo);
	this->addChild(path);

	// ��ʼ�������࣬������¼·���Ƿ��Ѿ�����
	handle = GraphHandle::create(parseXml, parseXml->cnt);
}


void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	if(touch)
	{
		location1 = touch->getLocation();
		if(containsInTouch(location1))
		{
			if(!isStart)
			{
				isStart = true;
				drawLine = LineDraw::create();
				drawLine->retain();
				drawLine->setGraphHandle(handle);
				drawLine->setArrayPoint(arrayPointDraw);
				this->addChild(drawLine, 1);

				drawLine->setFixPoint(location1);
				drawLine->setMovedPoint(location1);

				// ����location1���ڵ�
				//handle->saveDrawedLine(parseXml, beginIndex, beginIndex);

				// ��update�߼��жϵ��Ƿ�����Ȧ��
				isInCircle = true;
			}
			else
			{
				// ����Ѿ���ʼ�ˣ��򱣴��µ�һ����
				if(oldBeginIndex != beginIndex)
				{
					// �����µ����
// 					drawLine->setFixPoint(arrayPointDraw[beginIndex]);
// 					drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
// 					
// 					handle->saveDrawedLine(parseXml, oldBeginIndex, beginIndex);
					if(isOriginalPath(oldBeginIndex, beginIndex) && !isDrawed(oldBeginIndex, beginIndex))
					{
						drawLine->setFixPoint(arrayPointDraw[beginIndex]);
						drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
						drawLine->setBeginIndex(beginIndex);
						drawLine->setOldBeginIndex(oldBeginIndex);
						handle->saveDrawedLine(parseXml, oldBeginIndex, beginIndex);
					}
					// ����������Ѿ��������򱣳ֲ���
					else
					{
						// do nothing
					}
				}

			}
		}
	}
}

void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	if(touch && isInCircle)
	{
		location2 = touch->getLocation();
		drawLine->setMovedPoint(location2);
		// ������������н���ĳ��Ȧ�ķ�Χ�� ��Ȧ��������Ϊ�´ε���ʼ��
		if(containsInTouch(location2))
		{
			if(oldBeginIndex != beginIndex)
			{
				// ���������û�л�����������ȷ·���ϣ��������µ���㣬���������
				if(isOriginalPath(oldBeginIndex, beginIndex) && !isDrawed(oldBeginIndex, beginIndex))
				{
					drawLine->setFixPoint(arrayPointDraw[beginIndex]);
					drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
					drawLine->setBeginIndex(beginIndex);
					drawLine->setOldBeginIndex(oldBeginIndex);
					handle->saveDrawedLine(parseXml, oldBeginIndex, beginIndex);
				}
				// ����������Ѿ��������򱣳ֲ���
				else
				{
					// do nothing
				}
			}			
		}
	}

}

void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	location3 = touch->getLocation();
	if(isFinishPath())	
		CCMessageBox("win", (parseXml->dot_name).c_str());
}
// �жϵ���ĵ��Ƿ��ڷ�Χ��
bool GameScene::containsInTouch(CCPoint touchPoint)
{
	oldBeginIndex = beginIndex;
	for (size_t i = 0; i < arrayPointDraw.size(); i++)
		if((touchPoint.x - arrayPointDraw[i].x)*(touchPoint.x - arrayPointDraw[i].x) + pow(touchPoint.y - arrayPointDraw[i].y, 2) < pow((float)POINT_RADIUS, 2))
		{
			beginIndex = i;
			return true;
		}
		return false;

}
// �ж������߶��Ƿ��Ѿ�����

bool GameScene::isDrawed(int start, int end)
{
	if((start != end) && start >= 0 && end >= 0)
	{
		// ����ͼ�����������߶��Ƿ��Ѿ�����
		EdgeNode* find = handle->agl.adList[start].firstAdNode;
		while (find != NULL)
		{
			if(find->index != end)
				find = find->next;
			else
			{
				if(find->IsDrawed == true){
					beginIndex = oldBeginIndex;
					return true;}
				else
					return false;
			}
		}
	}
	return false;
}
// �ж������߶��Ƿ�����ȷ·����Χ��
bool GameScene::isOriginalPath(int start, int end)
{
	// ��Ϊ������� ����ֻ���ж�һ��
	if((start != end) && start >= 0 && end >= 0)
	{
		EdgeNode* find = handle->agl.adList[start].firstAdNode;
		while (find != NULL)
		{
			if(find->index == end)
				return true;
			find = find->next;
		}
	}
	// ���������ȷ·���ϣ����յ�ָ�����
	beginIndex = oldBeginIndex;
	return false;
}

// judge the player finish the game or not
// TODO: change the hard code "i<4" , 'i' is the number of this level
bool GameScene::isFinishPath()
{
	for(int i = 0; i < parseXml->cnt; i++)
	{
		EdgeNode* find = handle->agl.adList[i].firstAdNode;
		while (find != NULL)
		{
			if (find->IsDrawed == false)
				return false;
			else
				find = find->next;
		}
	}
	return true;
}