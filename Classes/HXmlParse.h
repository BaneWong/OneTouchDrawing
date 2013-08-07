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
	~HXmlParse();
	vector< string> allData;//用于记录所有数据
	vector<float> arrayPosX;
	vector<float> arrayPosY;
	vector<CCPoint> arrayPoint;
	vector<vector<int> > arrayConnect;

	string dot_name;
	string line_name;
	int dot_index;
	int cnt; // 点的总个数

	//  使用 CCSAXDelegator 重写3个回调函数
	//开始解析时回调
	void startElement(void *ctx, const char *name, const char **atts);
	//结束解析回调
	void endElement(void *ctx, const char *name);
	//键值对的结束字段
	void textHandler(void *ctx, const char *ch, int len);

private:

	string startXmlElement;//用来记录每个key前字段

	string endXmlElement;//用来记录每个key后字段

	string currString;//记录每个value的值
};

#endif /* defined(__ParseXmlTest__HXmlParse__) */