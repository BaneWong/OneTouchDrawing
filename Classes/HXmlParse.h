//
//  HXmlParse.h
//  ParseXmlTest
//
//  Created by Himi on 12-10-14.
//
//

#ifndef __ParseXmlTest__HXmlParse__
#define __ParseXmlTest__HXmlParse__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class HXmlParse :public CCObject, public CCSAXDelegator
{

public:
	HXmlParse();

	static HXmlParse * parserWithFile(const char *tmxFile);
	bool initHXmlParse(const char* xmlName);
	string root_name;
	bool isJumpHeadData;
	
	vector< string> allData;//���ڼ�¼��������
	vector<float> arrayPosX;
	vector<float> arrayPosY;
	vector<CCPoint> arrayPoint;
	vector<vector<int> > arrayConnect;

	string dot_name;
	string line_name;
	int dot_index;
	int cnt; // ����ܸ���

	//  ʹ�� CCSAXDelegator ��д3���ص�����
	//��ʼ����ʱ�ص�
	void startElement(void *ctx, const char *name, const char **atts);
	//���������ص�
	void endElement(void *ctx, const char *name);
	//��ֵ�ԵĽ����ֶ�
	void textHandler(void *ctx, const char *ch, int len);

private:

	string startXmlElement;//������¼ÿ��keyǰ�ֶ�

	string endXmlElement;//������¼ÿ��key���ֶ�

	string currString;//��¼ÿ��value��ֵ
};

#endif /* defined(__ParseXmlTest__HXmlParse__) */