// TODO:�ж��ظ����� ��Ҫ��

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
	// �Զ������ڷ�Χ�ڵĵ�����Ϊ������
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

	CCLabelTTF *pLabel=CCLabelTTF::create("xml read data��", "Arial", 28);
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	pLabel->setPosition(ccp(size.width/2,size.height-20));
	this->addChild(pLabel,1);

	// ���������ļ� ��ʼ���ؿ�
	
	std::ostringstream oss;
	oss << m_nLevelID;
	string parase_file = "path" + oss.str() + ".xml";
	parseXml = HXmlParse::parserWithFile(parase_file.c_str());//xml�ļ�


	pointCnt = parseXml->arrayPoint.size();
	for (int i = 0; i < pointCnt; i++)
		arrayPointDraw.push_back(parseXml->arrayPoint[i]);

	// �������е�ÿ�������ӵĵ㼯����ȡ����
	arrayConnectTo = parseXml->arrayConnect;

	//
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
	if(touch)
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
}
// �жϵ���ĵ��Ƿ��ڷ�Χ��
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