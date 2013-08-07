// To be Add:判断重复的线 不要画

#include "GameScene.h"


using namespace cocos2d;

CCScene* GameScene::scene()
{
	CCScene* scene = CCScene::create();

	GameScene* layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	beginIndex = -1;
	oldBeginIndex = -1;
	isInCircle = false;
	isStart = false;

	createOriginalPath();
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	// 自动将落在范围内的点设置为正中央
 	if(isInCircle)
 	{
 		drawLine->setFixPoint(arrayPointDraw[beginIndex]);
 		//drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
 	}
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void GameScene::createOriginalPath()
{

	CCLabelTTF *pLabel=CCLabelTTF::create("xml 文件中读取的数据如下：", "Arial", 28);
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	pLabel->setPosition(ccp(size.width/2,size.height-20));
	this->addChild(pLabel,1);

	// 解析配置文件 初始化关卡
	parseXml=HXmlParse::parserWithFile("path1.xml");//xml文件


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
					drawLine->setFixPoint(arrayPointDraw[beginIndex]);
					drawLine->setMovedPoint(arrayPointDraw[beginIndex]);

					// 保存已经画好的线的起点
					arrayPointBegin.push_back(arrayPointDraw[oldBeginIndex]);
					drawLine->setBeginPoint(arrayPointBegin);

					// 保存已经画好的线的终点
					arrayPointEnd.push_back(arrayPointDraw[beginIndex]);
					drawLine->setEndPoint(arrayPointEnd);

					//drawLine->setGraphHandle(handle);
					
					handle->saveDrawedLine(parseXml, oldBeginIndex, beginIndex);
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
		if(containsInTouch(location2) && (oldBeginIndex != beginIndex))
		{
			drawLine->setFixPoint(arrayPointDraw[beginIndex]);
			drawLine->setMovedPoint(arrayPointDraw[beginIndex]);
			drawLine->setBeginIndex(beginIndex);
			drawLine->setOldBeginIndex(oldBeginIndex);
			handle->saveDrawedLine(parseXml, oldBeginIndex, beginIndex);
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
