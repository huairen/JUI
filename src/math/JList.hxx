#ifndef JLIST_H_
#define JLIST_H_

class JListPtr
{
	struct Node
	{
		void* data;
		Node* prev;
		Node* next;
	};

public:
	JListPtr();
	~JListPtr();

	void PushBack(void* obj);
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