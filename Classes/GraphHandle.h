#ifndef __GRAPH_HANDLE_H__
#define __GRAPH_HANDLE_H__

#include "HXmlParse.h"

using namespace std;

#define  MAXNODE 10 //��󶥵���
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
typedef struct AdjGraphList{
	AdList adList;
	int nodeNum;// ������
}AdjGraphList;

class GraphHandle{
public:
	GraphHandle();
	~GraphHandle();
	// ���������ļ���ʼ��������
	static GraphHandle* create(HXmlParse* parase, int cnt);
	// �����Ѿ���������
	void saveDrawedLine(HXmlParse* parase,int begin, int end);
	AdjGraphList agl;
};


#endif __GRAPH_HANDLE_H__