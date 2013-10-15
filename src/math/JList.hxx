#ifndef JLIST_H_
#define JLIST_H_

class JPtrList
{
	struct Node
	{
		void* data;
		Node* prev;
		Node* next;
	};

public:
	JPtrList();
	~JPtrList();

	void PushBack(void *obj);
	void Pop(void *obj);
	void* First();
	void* Next();
	int GetCount();

private:
	Node *m_pHead;
	Node *m_pTail;
	Node *m_pWork;
	int m_nCount;
};

#endif