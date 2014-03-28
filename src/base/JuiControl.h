#ifndef JUI_CONTROL_H_
#define JUI_CONTROL_H_

#include "JuiTypes.h"
#include "JuiEventManager.h"
#include "Object/JObject.h"
#include "math/JRect.h"

class JDrawable;
class JuiContainer;
class JuiLayoutParameter;

class JuiControl : public JObject
{
	JDECLARE_ABSTRACT_CLASS(JuiControl)

	enum ControlState
	{
		STATE_VISIBLE			= 0x0001,
		STATE_ENABLE			= 0x0002,
		STATE_FOCUSED			= 0x0004,
		STATE_SELECTED			= 0x0008,
		STATE_READONLY			= 0x0040,
		STATE_MOUSE_ENABLE		= 0x0080,
		STATE_KEYBOARD_ENABLE	= 0x0100,
		STATE_CONTAINER			= 0x0200,
	};

public:
	JuiControl();
	virtual ~JuiControl();

	virtual JuiControl* Clone();

	JuiControl* GetRoot();
	virtual JuiEventManager *GetInputGenerator() { return NULL; }

	virtual void AddUpdateRegion(const JPoint2I& pos, const JPoint2I& size) {}
	void SetUpdateRegion(const JPoint2I& pos, const JPoint2I& size);
	void SetUpdate();

	void MouseLock();
	void MouseUnlock();
	bool IsMouseLocked();

	void SetName(const char* name);
	const char* GetName();

	void SetParent(JuiContainer* control);
	JuiContainer* GetParent();

	void SetBackground(const std::string& drawable);
	JDrawable *GetDrawable();

	void SetLayoutParameter(JuiLayoutParameter *pParam);
	JuiLayoutParameter *GetLayoutParameter();


	// @ point and size
	// @ {
public:
	//set point and size
	void SetBounds(const JPoint2I& position, const JPoint2I& extent);
	void SetBounds(const JRectI& bounds);

	void SetPosition(const JPoint2I& point);
	void SetPosition(int x, int y);
	void SetPosX(int x);
	void SetPosY(int y);

	void SetExtent(const JPoint2I& size);
	void SetExtent(int width, int height);
	void SetWidth(int width);
	void SetHeight(int height);

	void SetMinSize(int width, int height);
	void SetMinSize(const JPoint2I& size);
	void SetMaxSize(int width, int height);
	void SetMaxSize(const JPoint2I& size);

	//get point and size
	const JRectI& GetBounds() const;
	const JPoint2I& GetPosition() const;
	const JPoint2I& GetExtent() const;

	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetRight() const;
	int GetBottom() const;

	bool IsPointIn(const JPoint2I& pt);
	JPoint2I LocalToRoot(const JPoint2I &pos);
	// @ }



	// @ state
	// @ {
public:
	bool IsVisible() const;
	bool IsEnable() const;
	bool IsFocused() const;
	bool IsMouseEnable() const;
	bool IsKeyboardEnable() const;
	bool IsContainer() const;

	void SetVisible(bool value);
	void SetEnable(bool value);
	void SetMouseEnable(bool value);

protected:
	bool HasState(int flag) const;
	virtual void AddState(int flag);
	virtual void RemoveState(int flag);
	// @ }
	

	// @ event
	// @ {
public:
	void NotifySiblings(int message, int param);
	virtual void OnControlEvent(JuiControl* sender, int message, int param) {}

	virtual void OnMouseEnter() {}
	virtual void OnMouseLeave() {}
	virtual void OnMouseDown(const MouseEventInfo& event) {}
	virtual void OnMouseUp(const MouseEventInfo& event) {}
	virtual void OnMouseMove(const MouseEventInfo& event) {}

	virtual void OnKeyDown() {}

	virtual void OnSizeChanged(const JPoint2I& newSize) {}
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);
	// @ }


protected:
	std::string m_Name;
	uint32_t m_nState;
	JRectI m_rcBounds;
	JPoint2I m_ptMinSize;
	JPoint2I m_ptMaxSize;

	JDrawable *m_pBackground;
	JuiContainer *m_pParent;
	JuiLayoutParameter *m_pLayoutParam;
};

#include "JuiControl.inl"

#endif 