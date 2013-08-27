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
	HXmlParse* parseXml; // xml������
	vector<CCPoint> arrayPointDraw; // Ҫ���Ƶ�point����
	int pointCnt; // point����

	vector<vector<int> > arrayConnectTo;// xml��ÿ����Ҫ���ӵĵ�ļ���
	vector<CCPoint> arrayPointBegin;// ���������û����������
	vector<CCPoint> arrayPointEnd;// ���������û��������յ�

	CCPoint location1;// ��ʼ������
	CCPoint location2;// �ƶ��еĴ�����
	CCPoint location3;// �ſ�ʱ�Ĵ�����
	int beginIndex; //����ĵ�����
	int oldBeginIndex;// ��δ�����µ���ǰ�ĵ�����

	bool beginDrawFlag;// �Ƿ���Կ�ʼ����
	bool isInCircle; // �жϵ��Ƿ�����Ȧ��
	bool isStart; // ����Ƿ��Ѿ���ʼ���� ��һ�δ���Ҫ����Ȧ�ڲ��㿪ʼ
	LineDraw* drawLine; // ���·��
	LinePath* path;// ��ʶ·��
	GraphHandle *handle;//��ʼ������·���������
	
	int m_nLevelID;// stores the level ID choosed by the player

};

#endif  // __GAME_SCENE_H__