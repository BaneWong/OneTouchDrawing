#include "GraphHandle.h"

/*
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
 typedef struct{
 AdList adList;
 int nodeNum,edgeNum;// 顶点数和边数
 }GraphHandle;
 
 */
GraphHandle::GraphHandle()
{
	agl.nodeNum = 0;
    for(int i = 0; i < MAXNODE; i++){
        agl.adList[i].index = i;
        agl.adList[i].firstAdNode = NULL;
    }
    
}
GraphHandle::~GraphHandle()
{

}

GraphHandle* GraphHandle::create(HXmlParse* parase, int cnt)
{
	GraphHandle* gh = new GraphHandle();
	EdgeNode* pe = NULL;
	//EdgeNode* qe = NULL;
	//gh->agl->adList[0].firstAdNode = {-1, false, NULL};
    //gh->agl->nodeNum = cnt;
	// 初始化该关的图结构 cnt 为点的个数
	if(gh)
	{
		for(int i = 0; i < cnt; i++)
		{		
			for(int j = 0; j < parase->arrayConnect[i].size(); j++)
			{
				pe = (EdgeNode*)malloc(sizeof(struct EdgeNode));
				pe->index = parase->arrayConnect[i][j];
				pe->IsDrawed = false;
				pe->next = gh->agl.adList[i].firstAdNode;
				gh->agl.adList[i].firstAdNode = pe;
			}
			//gh->agl.adList[i].firstAdNode->next = NULL;
		}
		gh->agl.nodeNum = cnt;
		return gh;
	}
	CC_SAFE_DELETE(gh);
	return NULL;
}

void GraphHandle::saveDrawedLine(HXmlParse* parase, int begin, int end)
{
	// 从parase->arrayPoint[]的邻接点中遍历 逐一取出isDrawed的值
	// 如果已经是true，则不管 ，如果是false 则变为true
	EdgeNode* find = agl.adList[begin].firstAdNode;
	while(find != NULL && (begin != end))
	{
		if(find->index != end)
			find = find->next;
		else
		{
		find->IsDrawed = true;
		// 无向图 因此相应修改对应线段权值
		EdgeNode* findEnd = agl.adList[end].firstAdNode;
		while(findEnd != NULL)
		{
			if(findEnd->index != begin)
				findEnd = findEnd->next;
			else
			{
				findEnd->IsDrawed = true;
				break;
			}
		}
		break;		
		}
	}		
}