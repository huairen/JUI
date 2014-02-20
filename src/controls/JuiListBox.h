#ifndef JUI_LISTBOX_H_
#define JUI_LISTBOX_H_

#include "base/JuiControl.h"
#include "DataType/JArray.h"
#include "Graphics/JTexture2D.h"

class JuiListBox : public JuiControl
{
	JDECLARE_DYNAMIC_CLASS(JuiListBox)
	typedef JuiControl Parent;

protected:
	struct Item
	{
		std::string itemText;
		JuiControl *ctrl;
		bool isSelected;
		void *itemData;
	};

public:
	JuiListBox();
	~JuiListBox();

	virtual void OnMouseDown(const MouseEventInfo& event);
	virtual void OnMouseUp(const MouseEventInfo& event);
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

	void SetItemModel(JuiControl *pCtrl);
	int GetItemCount();
	int GetSelCount();

	void AddItem(const char* text, void *itemData = NULL);
	void InsertItem(int index, const char *text, void *itemData = NULL);
	JuiControl* PushDefaultItem();


	void DeleteItem(int index);
	void ClearItems();

	void UpdateSize(int index, int count);

protected:
	JArray<Item> m_lsItems;
	JArray<Item> m_lsSelectedItems;
	JuiControl *m_pItemModel;
};

JFORCE_LINK_OBJ(JuiListBox)

inline int JuiListBox::GetItemCount()
{
	return m_lsItems.GetCount();
}

inline int JuiListBox::GetSelCount()
{
	return m_lsSelectedItems.GetCount();
}

inline void JuiListBox::SetItemModel(JuiControl *pCtrl)
{
	m_pItemModel = pCtrl;
}

#endif