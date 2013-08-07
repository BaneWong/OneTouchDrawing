#ifndef __GRAPH_HANDLE_H__
#define __GRAPH_HANDLE_H__

#include "HXmlParse.h"

using namespace std;

#define  MAXNODE 10 //最大顶点数
typedef bool IsDrawed ;

// 边表
typedef struct EdgeNode{
	int index;
	IsDrawed IsDrawed;// 这条边是否已经画过了
	struct EdgeNode* next;// 指向该点的下一个相邻的顶点
}EdgeNode;

// 顶点表
typedef struct AdNode{
	int index; // 顶点序号
	struct EdgeNode* firstAdNode;// 指向第一个邻接顶点
}AdList[MAXNODE];

// 邻接表
typedef struct AdjGraphList{
	AdList adList;
	int nodeNum;// 顶点数
}AdjGraphList;

class GraphHandle{
public:
	GraphHandle();
	~GraphHandle();
	// 根据配置文件初始化处理类
	static GraphHandle* create(HXmlParse* parase, int cnt);
	// 保存已经画过的线
	void saveDrawedLine(HXmlParse* parase,int begin, int end);
	AdjGraphList agl;
};


#endif __GRAPH_HANDLE_H__