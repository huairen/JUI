#ifndef JUI_CONTROL_H_
#define JUI_CONTROL_H_

#include "JuiTypes.hxx"
#include "JuiInputManager.hxx"
#include "math/JRect.hxx"
#include "graphics/JRender.hxx"

enum ControlFlags
{
	CTRL_FLAG_VISIBLE			= 0x0001,
	CTRL_FLAG_ENABLE			= 0x0002,
	CTRL_FLAG_FOCUSED			= 0x0004,
	CTRL_FLAG_SELECTED			= 0x0008,
	CTRL_FLAG_READONLY			= 0x0040,
	CTRL_FLAG_MOUSE_ENABLE		= 0x0080,
	CTRL_FLAG_KEYBOARD_ENABLE	= 0x0100,
	CTRL_FLAG_CONTAINER			= 0x0200,
};

enum HorizAlignOptions
{
	CTRL_HORIZ_ALIGN_LEFT,
	CTRL_HORIZ_ALIGN_RIGHT,
	CTRL_HORIZ_ALIGN_CENTER,
	CTRL_HORIZ_ALIGN_WIDTH,
};

enum VertAlignOptions
{
	CTRL_VERT_ALIGN_TOP,
	CTRL_VERT_ALIGN_BOTTOM,
	CTRL_VERT_ALIGN_CENTER,
	CTRL_VERT_ALIGN_HEIGHT,
};

enum ScaleMode
{
	CTRL_SCALE_ALL,
	CTRL_SCALE_CENTER,
	CTRL_SCALE_SIDE,
};

enum ControlMessage
{
	CTRL_MSG_CLICK,
	CTRL_MSG_RADIO_CLICK,
};

class JuiContainer;

class JuiControl
{
public:
	JuiControl();
	virtual ~JuiControl();

	void SetName(const char* name);
	const char* GetName();

	void SetParent(JuiContainer* control);
	JuiContainer* GetParent();

	JuiControl* GetRoot();
	virtual JuiInputManager *GetInputGenerator() { return NULL; }

	void SetHorizAlign(HorizAlignOptions horiz);
	void SetVertAlign(VertAlignOptions vert);
	void SetScaleMode(ScaleMode mode);

	void SetUpdate();
	virtual void SetUpdateRegion(JPoint2I pos, JPoint2I size) {}

	void MouseLock();
	void MouseUnlock();
	bool IsMouseLocked();

public:
	// @ point and size
	// @ {
	//set point and size
	virtual void SetBounds(const JPoint2I& point, const JPoint2I& size);
	void SetBounds(const JRectI& bounds);
	void SetBounds(int x, int y, int width, int height);

	void SetPosition(const JPoint2I& point);
	void SetPosition(int x, int y);

	void SetSize(const JPoint2I& size);
	void SetSize(int width, int height);
	void SetWidth(int width);
	void SetHeight(int height);

	void SetMinSize(int width, int height);
	void SetMaxSize(int width, int height);

	//get point and size
	const JPoint2I& GetPosition();
	const JPoint2I& GetSize();

	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
	int GetRight();
	int GetBottom();

	bool IsPointIn(const JPoint2I& pt);
	JPoint2I LocalToRoot(const JPoint2I &pos);
	// @ }


public:
	// @ flags
	// @ {
	bool IsVisible();
	bool IsEnable();
	bool IsFocused();
	bool IsMouseEnable();
	bool IsKeyboardEnable();
	bool IsContainer();
	bool HasFlag(int flag);
	virtual void AddFlag(int flag);
	virtual void RemoveFlag(int flag);
	// @ }
	

public:
	// @ event
	// @ {
	void OnParentResized(const JRectI &oldRect, const JRectI &newRect);
	void OnChildResized(JuiControl *child);

	void NotifySiblings(int message, int param);
	virtual void OnControlEvent(JuiControl* sender, int message, int param) {}

	virtual void OnMouseEnter() {}
	virtual void OnMouseLeave() {}
	virtual void OnMouseDown(const MouseEventInfo& event) {}
	virtual void OnMouseUp(const MouseEventInfo& event) {}
	virtual void OnMouseMove(const MouseEventInfo& event) {}

	virtual void OnKeyDown() {}

	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint) = 0;
	// @ }


protected:
	void DrawImage(JImage* img, const JPoint2I &offset, const JRectI &rcPaint);
	void DrawImageScaleCenter(JImage* img, const JPoint2I &offset, JRectI &rcPaint);


protected:
	char m_szName[32];
	uint32_t m_nFlags;
	HorizAlignOptions m_HorizAlign;
	VertAlignOptions m_VerzAlign;
	ScaleMode m_ScaleMode;

	JuiContainer *m_pParent;

	JRectI m_rcBounds;
	JPoint2I m_ptMinSize;
	JPoint2I m_ptMaxSize;

	static JRender* sm_pRender;
};

#include "JuiControl.inl"

#endif 