#ifndef JUI_LISTBOX_H_
#define JUI_LISTBOX_H_

#include "JuiContainer.h"
#include "graphics/JImage.h"

class JuiListBox : public JuiContainer
{
	typedef JuiContainer Parent;
protected:
	struct Item
	{
		const char *itemText;
		bool isSelected;
		void *itemData;
	};

public:
	JuiListBox();
	~JuiListBox();

	virtual void OnMouseDown(const MouseEventInfo& event);
	virtual void OnMouseUp(const MouseEventInfo& event);
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

	virtual void OnRenderItem(JRectI itemRect, Item *item);

	int GetItemCount();
	int GetSelCount();

	int AddItem(const char* text, void *itemData = NULL);
	int InsertItem(int index, const char *text, void *itemData = NULL);

	void DeleteItem(int index);
	void ClearItems();

	void UpdateSize();

protected:
	JList m_lsItems;
	JList m_lsSelectedItems;
};

inline int JuiListBox::GetItemCount()
{
	return m_lsItems.GetCount();
}

inline int JuiListBox::GetSelCount()
{
	return m_lsSelectedItems.GetCount();
}

#endif