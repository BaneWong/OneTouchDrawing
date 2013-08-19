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
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameScene);

	// ��ʼpath
	void createOriginalPath();


	void update(float dt);

	bool containsInTouch(CCPoint);
	bool isDrawed(int start, int end);
	bool isOriginalPath(int start, int end);

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

};

#endif  // __GAME_SCENE_H__