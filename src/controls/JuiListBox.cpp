#include "JuiListBox.h"
#include "container/JuiContainer.h"

JIMPLEMENT_FORCE_LINK_OBJ(JuiListBox)
JIMPLEMENT_DYNAMIC_CLASS(JuiListBox, JuiControl)

JuiListBox::JuiListBox()
	: m_pItemModel(NULL)
{
}

JuiListBox::~JuiListBox()
{

}

void JuiListBox::OnMouseDown( const MouseEventInfo& event )
{

}

void JuiListBox::OnMouseUp( const MouseEventInfo& event )
{

}

void JuiListBox::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	for (int i=0; i<m_lsItems.GetCount(); ++i)
	{
		Item* pItem = static_cast<Item*>(m_lsItems.At(i));
		if(pItem->ctrl != NULL)
		{
			pItem->ctrl->OnRender(offset, rcPaint);
			continue;
		}
	}
	
}

void JuiListBox::AddItem( const char* text, void *itemData /*= NULL*/ )
{
	if( !text )
		return;

	Item *newItem = m_lsItems.Increment();
	if( !newItem )
		return;

	newItem->itemText    = text;
	newItem->itemData    = itemData;
	newItem->isSelected  = false;

	UpdateSize(m_lsItems.GetCount() - 1, 1);
}

void JuiListBox::InsertItem( int index, const char *text, void *itemData /*= NULL*/ )
{
	if( !text )
		return;

	if( index >= m_lsItems.GetCount() )
		index = m_lsItems.GetCount();

	Item *newItem = m_lsItems.Increment();
	if( !newItem )
		return;

	newItem->itemText    = text;
	newItem->itemData    = itemData;
	newItem->isSelected  = false;

	UpdateSize(index, m_lsItems.GetCount() - index);
}

JuiControl* JuiListBox::PushDefaultItem()
{
	if(m_pItemModel == NULL)
		return NULL;

	JuiControl* pClone = m_pItemModel->Clone();
	if(pClone == NULL)
		return NULL;

	pClone->SetVisible(true);

	Item *newItem = m_lsItems.Increment();
	if( !newItem )
		return NULL;

	newItem->itemText.clear();
	newItem->itemData    = NULL;
	newItem->isSelected  = false;
	newItem->ctrl = pClone;

	UpdateSize(m_lsItems.GetCount() - 1, 1);

	return pClone;
}

void JuiListBox::DeleteItem( int index )
{

}

void JuiListBox::ClearItems()
{

}

void JuiListBox::UpdateSize( int index, int count )
{
	if(index + count > m_lsItems.GetCount())
		count = m_lsItems.GetCount() - index;

	int nPosX = 0;
	int nPosY = 0;

	for (int i=index; i<count; ++i)
	{
		Item* pItem = m_lsItems.At(i);
		if(pItem->ctrl != NULL)
		{
			JuiControl* pCtrl = pItem->ctrl;
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
