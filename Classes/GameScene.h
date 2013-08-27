#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "GraphHandle.h"

#include "HXmlParse.h"

#include "LineDraw.h"

#include "LinePath.h"

USING_NS_CC;



class GameScene : public CCLayer
{
public:

	~GameScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(int levelID);

	// need to pass the levelID
	static GameScene* create(int levelID);

	// TODO:change to the return callback
	void menuCloseCallback(CCObject* pSender);
	void returnCallback(CCObject* pSender);
	void restartCallback(CCObject* pSender);

	// init the original path
	void createOriginalPath();

	void update(float dt);

	bool containsInTouch(CCPoint);
	bool isDrawed(int start, int end);
	bool isOriginalPath(int start, int end);
	bool isFinishPath();

	void createRestartAndBackMenu();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

private:
	HXmlParse* parseXml; // xml解析类
	vector<CCPoint> arrayPointDraw; // 要绘制的point集合
	int pointCnt; // point数量

	vector<vector<int> > arrayConnectTo;// xml中每个点要连接的点的集合
	vector<CCPoint> arrayPointBegin;// 用来保存用户画过的起点
	vector<CCPoint> arrayPointEnd;// 用来保存用户画过的终点

	CCPoint location1;// 初始触摸点
	CCPoint location2;// 移动中的触摸点
	CCPoint location3;// 放开时的触摸点
	int beginIndex; //点击的点的序号
	int oldBeginIndex;// 还未划出新的线前的点的序号

	bool beginDrawFlag;// 是否可以开始划线
	bool isInCircle; // 判断点是否落在圈内
	bool isStart; // 玩家是否已经开始划线 第一次触碰要落在圈内才算开始
	LineDraw* drawLine; // 玩家路径
	LinePath* path;// 初识路径
	GraphHandle *handle;//初始化处理路径保存的类
	
	int m_nLevelID;// stores the level ID choosed by the player

};

#endif  // __GAME_SCENE_H__