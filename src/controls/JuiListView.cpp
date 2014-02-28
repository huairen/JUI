#include "JuiListView.h"
#include "container/JuiContainer.h"

JIMPLEMENT_FORCE_LINK_OBJ(JuiListView)
JIMPLEMENT_DYNAMIC_CLASS(JuiListView, JuiControl)

JuiListView::JuiListView()
	: m_pItemModel(NULL)
{
}

JuiListView::~JuiListView()
{

}

void JuiListView::OnMouseDown( const MouseEventInfo& event )
{

}

void JuiListView::OnMouseUp( const MouseEventInfo& event )
{

}

void JuiListView::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	for (int i=0; i<m_lsItems.GetCount(); ++i)
	{
		Item& pItem = m_lsItems.At(i);
		if(pItem.ctrl != NULL)
		{
			pItem.ctrl->OnRender(offset, rcPaint);
			continue;
		}
	}
	
}

void JuiListView::AddItem( const char* text, void *itemData /*= NULL*/ )
{
	if( !text )
		return;

	m_lsItems.Increment();

	Item& newItem = m_lsItems.Last();

	newItem.itemText    = text;
	newItem.itemData    = itemData;
	newItem.isSelected  = false;

	UpdateSize(m_lsItems.GetCount() - 1, 1);
}

void JuiListView::InsertItem( int index, const char *text, void *itemData /*= NULL*/ )
{
	if( !text )
		return;

	if( index >= m_lsItems.GetCount() )
		index = m_lsItems.GetCount();

	m_lsItems.Increment();

	Item &newItem = m_lsItems.Last();
	newItem.itemText    = text;
	newItem.itemData    = itemData;
	newItem.isSelected  = false;

	UpdateSize(index, m_lsItems.GetCount() - index);
}

JuiControl* JuiListView::PushDefaultItem()
{
	if(m_pItemModel == NULL)
		return NULL;

	JuiControl* pClone = m_pItemModel->Clone();
	if(pClone == NULL)
		return NULL;

	pClone->SetVisible(true);

	m_lsItems.Increment();

	Item &newItem = m_lsItems.Last();
	newItem.itemText.clear();
	newItem.itemData    = NULL;
	newItem.isSelected  = false;
	newItem.ctrl = pClone;

	UpdateSize(m_lsItems.GetCount() - 1, 1);

	return pClone;
}

void JuiListView::DeleteItem( int index )
{

}

void JuiListView::ClearItems()
{

}

void JuiListView::UpdateSize( int index, int count )
{
	if(index + count > m_lsItems.GetCount())
		count = m_lsItems.GetCount() - index;

	int nPosX = 0;
	int nPosY = 0;

	for (int i=index; i<count; ++i)
	{
		Item& pItem = m_lsItems.At(i);
		if(pItem.ctrl != NULL)
		{
			JuiControl* pCtrl = pItem.ctrl;
			if(i == index)
			{
				nPosX = pCtrl->GetPosX();
				nPosY = pCtrl->GetBottom();
			}
			else
			{
				pCtrl->SetPosition(nPosX, nPosY);
				nPosY += pCtrl->GetHeight();
			}

			pCtrl->SetWidth(GetWidth() - (nPosX*2));
		}
	}
}
