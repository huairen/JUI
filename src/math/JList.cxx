#include "JList.hxx"

JListPtr::JListPtr()
{
	m_pHead = 0;
	m_pTail = 0;
	m_pWork = 0;
	m_nCount = 0;
}

JListPtr::~JListPtr()
{

}

void JListPtr::PushBack( void* obj )
{
	Node* new_node = new Node;
	new_node->data = obj;
	new_node->prev = 0;
	new_node->next = 0;

	if(m_pTail)
	{
		m_pTail->next = new_node;
		new_node->prev = m_pTail;
	}

	m_pTail = new_node;

	if(!m_pHead)
		m_pHead = new_node;

	m_nCount++;
}

void* JListPtr::First()
{
	m_pWork = m_pHead;
	return m_pWork ? m_pWork->data : 0;
}

void* JListPtr::Next()
{
	if(m_pWork)
		m_pWork = m_pWork->next;

	return m_pWork ? m_pWork->data : 0;
}

int JListPtr::GetCount()
{
	return m_nCount;
}
