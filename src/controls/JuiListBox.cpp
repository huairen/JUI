#include "JuiListBox.h"

JIMPLEMENT_FORCE_LINK_OBJ(JuiListBox)
JIMPLEMENT_DYNAMIC_CLASS(JuiListBox, JuiControl)

JuiListBox::JuiListBox()
	: m_lsItems(sizeof(Item))
	, m_lsSelectedItems(sizeof(Item))
	, m_pItemModel(NULL)
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
}

void JuiListBox::OnRenderItem( JRectI itemRect, Item *item )
{

}

void JuiListBox::AddItem( const char* text, void *itemData /*= NULL*/ )
{
	if( !text )
		return;

	Item *newItem = (Item *)m_lsItems.Increment();
	if( !newItem )
		return;

	newItem->itemText    = text;
	newItem->itemData    = itemData;
	newItem->isSelected  = false;

	UpdateSize();
}

void JuiListBox::InsertItem( int index, const char *text, void *itemData /*= NULL*/ )
{
	if( !text )
		return;

	if( index >= m_lsItems.GetCount() )
		index = m_lsItems.GetCount();

	Item *newItem = (Item *)m_lsItems.IncrementAt(index);
	if( !newItem )
		return;

	newItem->itemText    = text;
	newItem->itemData    = itemData;
	newItem->isSelected  = false;

	UpdateSize();
}

void JuiListBox::PushDefaultItem()
{
	if(m_pItemModel == NULL)
		return;

	Item *newItem = (Item *)m_lsItems.Increment();
	if( !newItem )
		return;

	newItem->itemText.clear();
	newItem->itemData    = NULL;
	newItem->isSelected  = false;
	newItem->ctrl = static_cast<JuiControl*>(m_pItemModel->Clone());

	UpdateSize();
}

void JuiListBox::DeleteItem( int index )
{

}

void JuiListBox::ClearItems()
{

}

void JuiListBox::UpdateSize()
{

}
