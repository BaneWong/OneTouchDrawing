#include "GraphHandle.h"

/*
 typedef bool IsDrawed ;
 
 // �߱�
 typedef struct EdgeNode{
 int index;
 IsDrawed IsDrawed;// �������Ƿ��Ѿ�������
 struct EdgeNode* next;// ָ��õ����һ�����ڵĶ���
 }EdgeNode;
 
 // �����
 typedef struct AdNode{
 int index; // �������
 struct EdgeNode* firstAdNode;// ָ���һ���ڽӶ���
 }AdList[MAXNODE];
 
 // �ڽӱ�
 typedef struct{
 AdList adList;
 int nodeNum,edgeNum;// �������ͱ���
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
	// ��ʼ���ùص�ͼ�ṹ cnt Ϊ��ĸ���
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
	// ��parase->arrayPoint[]���ڽӵ��б��� ��һȡ��isDrawed��ֵ
	// ����Ѿ���true���򲻹� �������false ���Ϊtrue
	EdgeNode* find = agl.adList[begin].firstAdNode;
	while(find != NULL && (begin != end))
	{
		if(find->index != end)
			find = find->next;
		else
		{
		find->IsDrawed = true;
		// ����ͼ �����Ӧ�޸Ķ�Ӧ�߶�Ȩֵ
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