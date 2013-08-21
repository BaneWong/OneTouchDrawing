// TODO:判断重复的线 不要画

#include "GameScene.h"

using namespace cocos2d;

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

	createOriginalPath();
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	// 自动将落在范围内的点设置为正中央
//  	if(isInCircle)
//  	{
//  		drawLine->setFixPoint(arrayPointDraw[beginIndex]);
//  		//drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
//  	}
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void GameScene::createOriginalPath()
{
	CCLabelTTF *pLabel=CCLabelTTF::create("xml read data：", "Arial", 28);
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	pLabel->setPosition(ccp(size.width/2,size.height-20));
	this->addChild(pLabel,1);

	// 解析配置文件 初始化关卡
	
	// convert int to string
	std::ostringstream oss;
	oss << m_nLevelID;
	string parase_file = "path" + oss.str() + ".xml";	
	parseXml = HXmlParse::parserWithFile(parase_file.c_str());//xml文件

	pointCnt = parseXml->arrayPoint.size();
	for (int i = 0; i < pointCnt; i++)
		arrayPointDraw.push_back(parseXml->arrayPoint[i]);

	// 将配置中的每个点连接的点集合提取出来
	arrayConnectTo = parseXml->arrayConnect;

	//
	path = LinePath::create();
	path->setArrayDraw(arrayPointDraw);
	path->setPtCnt(pointCnt);
	path->setArrayConnect(arrayConnectTo);
	this->addChild(path);

	// 初始化处理类，用来记录路径是否已经保存
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
				drawLine->setGraphHandle(handle);
				drawLine->setArrayPoint(arrayPointDraw);
				this->addChild(drawLine, 1);

				drawLine->setFixPoint(location1);
				drawLine->setMovedPoint(location1);

				// 根据location1所在的
				//handle->saveDrawedLine(parseXml, beginIndex, beginIndex);

				// 供update逻辑判断点是否落在圈内
				isInCircle = true;
			}
			else
			{
				// 如果已经开始了，则保存新的一条线
				if(oldBeginIndex != beginIndex)
				{
					// 设置新的起点
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
					// 如果这条线已经画过，则保持不变
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
	if(touch)
	{
		location2 = touch->getLocation();
		drawLine->setMovedPoint(location2);
		// 如果滑动过程中进入某个圈的范围内 则将圈中心设置为下次的起始点
		if(containsInTouch(location2))
		{
			if(oldBeginIndex != beginIndex)
			{
				// 如果这条线没有画过并且在正确路径上，则设置新的起点，并保存该线
				if(isOriginalPath(oldBeginIndex, beginIndex) && !isDrawed(oldBeginIndex, beginIndex))
				{
					drawLine->setFixPoint(arrayPointDraw[beginIndex]);
					drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
					drawLine->setBeginIndex(beginIndex);
					drawLine->setOldBeginIndex(oldBeginIndex);
					handle->saveDrawedLine(parseXml, oldBeginIndex, beginIndex);
				}
				// 如果这条线已经画过，则保持不变
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
}
// 判断点击的点是否在范围内
bool GameScene::containsInTouch(CCPoint touchPoint)
{
	oldBeginIndex = beginIndex;
	for (int i = 0; i < arrayPointDraw.size(); i++)
		if((touchPoint.x - arrayPointDraw[i].x)*(touchPoint.x - arrayPointDraw[i].x) + pow(touchPoint.y - arrayPointDraw[i].y, 2) < pow((float)POINT_RADIUS, 2))
		{
			beginIndex = i;
			return true;
		}
		return false;

}
// 判断这条线段是否已经画过

bool GameScene::isDrawed(int start, int end)
{
	if((start != end) && start >= 0 && end >= 0)
	{
		// 遍历图，查找这条线段是否已经画过
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
// 判断这条线段是否在正确路径范围内
bool GameScene::isOriginalPath(int start, int end)
{
	// 因为是无向的 所以只需判断一边
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
	// 如果不在正确路径上，则将终点指回起点
	beginIndex = oldBeginIndex;
	return false;
}