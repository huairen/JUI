#include "JuiListBox.h"

JuiListBox::JuiListBox()
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

int JuiListBox::AddItem( const char* text, void *itemData /*= NULL*/ )
{
	if( !text )
		return -1;

	Item *newItem = new Item;
	if( !newItem )
		return -1;

	newItem->itemText    = _strdup(text);
	newItem->itemData    = itemData;
	newItem->isSelected  = false;

	m_lsItems.PushBack(newItem);

	UpdateSize();

	return m_lsItems.GetCount() - 1;
}

int JuiListBox::InsertItem( int index, const char *text, void *itemData /*= NULL*/ )
{
	if( !text )
		return -1;

	if( index >= m_lsItems.GetCount() )
		index = m_lsItems.GetCount();


	Item *newItem = new Item;
	if( !newItem )
		return -1;

	newItem->itemText    = _strdup(text);
	newItem->itemData    = itemData;
	newItem->isSelected  = false;

	m_lsItems.Insert(index, newItem);

	UpdateSize();

	return index;
}

void JuiListBox::DeleteItem( int index )
{

}

void JuiListBox::ClearItems()
{

}
