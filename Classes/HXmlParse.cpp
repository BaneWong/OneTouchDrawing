//
//  HXmlParse.cpp
//  ParseXmlTest
//
//  Created by Himi on 12-10-14.
//
//

#include "HXmlParse.h"
#include "platform/CCSAXParser.h"

using namespace std;

HXmlParse::HXmlParse():dot_name(""),line_name(""),dot_index(0),cnt(-1){}

HXmlParse * HXmlParse::parserWithFile(const char *tmxFile)
{
	HXmlParse *pRet = new HXmlParse();
	if(pRet->initHXmlParse(tmxFile))
	{
		for (int i = 0;i < pRet->arrayPosX.size();i++)
		{
			pRet->arrayPoint.push_back(ccp(pRet->arrayPosX[i], pRet->arrayPosY[i]));
		}
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool HXmlParse::initHXmlParse(const char* xmlName)

{
	CCSAXParser _par;
	if (false == _par.init("UTF-8") )
	{
		CCLog("请使用utf-8格式!");
		return false;
	}
	_par.setDelegator(this);
	//获取文件的完整相对路径
	string a = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlName);
	const char* _path =a.c_str();
	//	 CCFileUtils::sharedFileUtils()->fullPathForFilename("ball.wav").c_str()
	return _par.parse(_path);

}

vector<int> convertStrToArray(string strTmp)
{
	// 先处理第一个字符
	vector<int> tmpVector;
	string strFirst = strTmp.substr(0, 1);
	string strOthers = strTmp.substr(1, strTmp.size() - 1);
	string strOthersElement;
	tmpVector.push_back(atoi(strFirst.c_str()));
	size_t pos = 0;
	while( (pos = strOthers.find( ",", pos )) != string::npos ) 
	{		
		strOthersElement = strOthers.substr(pos + 1, 1);
		tmpVector.push_back(atoi(strOthersElement.c_str()));
		pos += 1;
	}
		
	
	return tmpVector;
}

//开始解析时回调
void HXmlParse::startElement(void *ctx, const char *name, const char **atts)

{
	CC_UNUSED_PARAM(ctx);

	startXmlElement = (char*)name;
	if(!isJumpHeadData){//跳过数据头
		CCLog("------跳过root name");
		isJumpHeadData=true;
		root_name=startXmlElement;
		return;
	}		
	if(line_name == "lineTo")
	{
		vector<int> tmpArray = convertStrToArray(currString);
		arrayConnect.push_back(tmpArray);
		line_name = "";
	}
	if(dot_name == "d" && startXmlElement == "lineTo")
	{
		line_name = startXmlElement;
	}
	if(startXmlElement[0] == 'd')
	{
		dot_name = "d";
		dot_index = atoi((startXmlElement.substr(startXmlElement.size()-1,1)).c_str());
	}

}
//结束解析回调
void HXmlParse::endElement(void *ctx, const char *name)

{
	CC_UNUSED_PARAM(ctx);

	endXmlElement = (char*)name;
	if(endXmlElement==root_name){//数据尾
		CCLog("读取xml结束");
		isJumpHeadData=false;
		root_name="";
		return;
	}
	if(endXmlElement == "cnt") 
		cnt = atoi(currString.c_str());
	// 处理最后一个dot 在startElement中没处理到
	if(dot_index == (cnt - 1) && line_name == "lineTo")
	{
		vector<int> tmpArray = convertStrToArray(currString);
		arrayConnect.push_back(tmpArray);
		dot_index = -1;
	}
}
//键值对的结束字段
void HXmlParse::textHandler(void *ctx, const char *ch, int len)
{

	CC_UNUSED_PARAM(ctx);
	currString=string((char*)ch,0,len);
	if(startXmlElement == "posX"){
		arrayPosX.push_back(atof(currString.c_str()));
	}
	else if (startXmlElement == "posY")
	{
		arrayPosY.push_back(atof(currString.c_str()));
	}
	else if (root_name == "dot1" && startXmlElement == "lineTo")
	{

	}


}
