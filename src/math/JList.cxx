#include "JList.hxx"

JPtrList::JPtrList()
{
	m_pHead = 0;
	m_pTail = 0;
	m_pWork = 0;
	m_nCount = 0;
}

JPtrList::~JPtrList()
{

}

void JPtrList::Insert( int index, void *obj )
{
	Node *node = m_pHead;
	while(node && index-- > 0)
		node = node->next;

	if(!node)
		node = m_pTail;

	Node* new_node = new Node;
	new_node->data = obj;
	new_node->prev = node->prev;
	new_node->next = node;

	if(node->prev)
		node->prev->next = new_node;

	node->prev = new_node;

	if(node == m_pHead)
		m_pHead = new_node;

	if(node == m_pTail)
		m_pTail = new_node;

	m_nCount++;
}

void JPtrList::Remove( int index )
{
	if(m_nCount == 0)
		return;

	Node *node = m_pHead;
	while(node && index-- > 0)
		node = node->next;

	if(!node)
		node = m_pTail;

	if(node->prev)
		node->prev->next = node->next;

	if(node->next)
		node->next->prev = node->prev;

	if(node == m_pHead)
		m_pHead = node->next;

	if(node == m_pTail)
		m_pTail = node->prev;

	m_nCount--;
}

void JPtrList::PushBack( void* obj )
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

void JPtrList::Pop( void *obj )
{
	Node *ptr = m_pHead;
	while(ptr)
	{
		if(obj == ptr->data)
			break;

		ptr = ptr->next;
	}

	if(ptr == 0)
		return;

	if(ptr->prev)
		ptr->prev->next = ptr->next;
	else
		m_pHead = ptr->next;

	if(ptr->next)
		ptr->next->prev = ptr->prev;
	else
		m_pTail = ptr->prev;

	delete ptr;
	m_nCount--;
}

void* JPtrList::First()
{
	m_pWork = m_pHead;
	return m_pWork ? m_pWork->data : 0;
}

void* JPtrList::Next()
{
	if(m_pWork)
		m_pWork = m_pWork->next;

	return m_pWork ? m_pWork->data : 0;
}

int JPtrList::GetCount()
{
	return m_nCount;
}
