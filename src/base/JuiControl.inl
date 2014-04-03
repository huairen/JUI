#ifndef JUI_CONTROL_INL_
#define JUI_CONTROL_INL_

inline void JuiControl::SetName(const char* name)
{
	m_Name = name;
}

inline const char* JuiControl::GetName()
{
	return m_Name.c_str();
}

inline void JuiControl::SetParent( JuiContainer* control )
{
	m_pParent = control;
}

inline JuiContainer*  JuiControl::GetParent()
{
	return m_pParent;
}

inline JDrawable *JuiControl::GetDrawable()
{
	return m_pBackground;
}

inline void JuiControl::SetLayoutParameter(JuiLayoutParameter *pParam)
{
	m_pLayoutParam = pParam;
}

inline JuiLayoutParameter * JuiControl::GetLayoutParameter()
{
	return m_pLayoutParam;
}


//---------------------------------------------------------------------------
inline void JuiControl::SetBounds(const JPoint2I& position, const JPoint2I& extent)
{
	SetPosition(position);
	SetExtent(extent);
}

inline void JuiControl::SetBounds( const JRectI& bounds )
{
	SetPosition(bounds.position);
	SetExtent(bounds.extent);
}

inline void JuiControl::SetExtent(const JPoint2I& size)
{
	if(m_rcBounds.extent != size)
	{
		m_rcBounds.extent = size;
		OnSizeChanged();
	}
}

inline void JuiControl::SetExtent( int width, int height )
{
	if(m_rcBounds.extent.x != width == m_rcBounds.extent.y != height)
	{
		m_rcBounds.extent.x = width;
		m_rcBounds.extent.y = height;
		OnSizeChanged();
	}
}

inline void JuiControl::SetWidth(int width)
{
	if(m_rcBounds.extent.x != width)
	{
		m_rcBounds.extent.x = width;
		OnSizeChanged();
	}
}

inline void JuiControl::SetHeight(int height)
{
	if(m_rcBounds.extent.y != height)
	{
		m_rcBounds.extent.y = height;
		OnSizeChanged();
	}
}

inline void JuiControl::SetMinSize( int width, int height )
{
	m_ptMinSize.x = width;
	m_ptMinSize.y = height;
}

inline void JuiControl::SetMinSize( const JPoint2I& size )
{
	m_ptMinSize = size;
}

inline void JuiControl::SetMaxSize( int width, int height )
{
	m_ptMaxSize.x = width;
	m_ptMaxSize.y = height;
}

inline void JuiControl::SetMaxSize( const JPoint2I& size )
{
	m_ptMaxSize = size;
}

//get point and size
inline const JRectI& JuiControl::GetBounds() const
{
	return m_rcBounds;
}

inline const JPoint2I& JuiControl::GetPosition() const
{
	return m_rcBounds.position;
}

inline const JPoint2I& JuiControl::GetExtent() const
{
	return m_rcBounds.extent;
}

inline int JuiControl::GetPosX() const
{
	return m_rcBounds.position.x;
}

inline int JuiControl::GetPosY() const
{
	return m_rcBounds.position.y;
}

inline int JuiControl::GetWidth() const
{
	return m_rcBounds.extent.x;
}

inline int JuiControl::GetHeight() const
{
	return m_rcBounds.extent.y;
}

inline int JuiControl::GetRight() const
{
	return m_rcBounds.position.x + m_rcBounds.extent.x;
}

inline int JuiControl::GetBottom() const
{
	return m_rcBounds.position.y + m_rcBounds.extent.y;
}

//---------------------------------------------------------------------------
//prop
inline bool JuiControl::IsVisible() const
{
	return (m_nState & STATE_VISIBLE) != 0;
}

inline bool JuiControl::IsEnable() const
{
	return (m_nState & STATE_ENABLE) != 0;
}

inline bool JuiControl::IsFocused() const
{
	return (m_nState & STATE_FOCUSED) != 0;
}

inline bool JuiControl::IsMouseEnable() const
{
	return (m_nState & STATE_MOUSE_ENABLE) != 0;
}

inline bool JuiControl::IsKeyboardEnable() const
{
	return (m_nState & STATE_KEYBOARD_ENABLE) != 0;
}

inline bool JuiControl::IsContainer() const
{
	return (m_nState & STATE_CONTAINER) != 0;
}

inline bool JuiControl::HasState(int flag) const
{
	return (m_nState & flag) != 0;
}

inline void JuiControl::AddState(int flag)
{
	m_nState |= flag;
}

inline void JuiControl::RemoveState(int flag)
{
	m_nState &= ~flag;
}

#endif