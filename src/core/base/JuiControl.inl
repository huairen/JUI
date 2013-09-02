
inline void JuiControl::SetName(const char* name)
{
	strcpy_s(m_szName, sizeof(m_szName), name);
}

inline void JuiControl::SetParent( JuiContainer* control )
{
	m_pParent = control;
}

inline JuiContainer*  JuiControl::GetParent()
{
	return m_pParent;
}

inline void JuiControl::SetHorizAlign(HorizAlignOptions horiz)
{
	m_HorizAlign = horiz;
}

inline void JuiControl::SetVertAlign(VertAlignOptions vert)
{
	m_VerzAlign = vert;
}

inline void JuiControl::SetScaleMode( ScaleMode mode )
{
	m_ScaleMode = mode;
}

inline const char* JuiControl::GetName()
{
	return m_szName;
}

//---------------------------------------------------------------------------
inline void JuiControl::SetBounds( const JRectI& bounds )
{
	SetBounds(bounds.position, bounds.extent);
}

inline void JuiControl::SetBounds( int x, int y, int width, int height )
{
	SetBounds(JPoint2I(x,y), JPoint2I(width, height));
}

inline void JuiControl::SetPosition(const JPoint2I& point)
{
	SetBounds(point, m_rcBounds.extent);
}

inline void JuiControl::SetPosition( int x, int y )
{
	SetBounds(JPoint2I(x,y), m_rcBounds.extent);
}

inline void JuiControl::SetExtent(const JPoint2I& size)
{
	SetBounds(m_rcBounds.position, size);
}

inline void JuiControl::SetExtent( int width, int height )
{
	SetBounds(m_rcBounds.position, JPoint2I(width, height));
}

inline void JuiControl::SetWidth(int width)
{
	SetExtent(width, m_rcBounds.extent.y);
}

inline void JuiControl::SetHeight(int height)
{
	SetExtent(m_rcBounds.extent.x, height);
}

inline void JuiControl::SetMinSize( int width, int height )
{
	m_ptMinSize.x = width;
	m_ptMinSize.y = height;
}

inline void JuiControl::SetMaxSize( int width, int height )
{
	m_ptMaxSize.x = width;
	m_ptMaxSize.y = height;
}

//get point and size
inline const JPoint2I& JuiControl::GetPosition()
{
	return m_rcBounds.position;
}

inline const JPoint2I& JuiControl::GetExtent()
{
	return m_rcBounds.extent;
}

inline int JuiControl::GetPosX()
{
	return m_rcBounds.position.x;
}

inline int JuiControl::GetPosY()
{
	return m_rcBounds.position.y;
}

inline int JuiControl::GetWidth()
{
	return m_rcBounds.extent.x;
}

inline int JuiControl::GetHeight()
{
	return m_rcBounds.extent.y;
}

inline int JuiControl::GetRight()
{
	return m_rcBounds.position.x + m_rcBounds.extent.x;
}

inline int JuiControl::GetBottom()
{
	return m_rcBounds.position.y + m_rcBounds.extent.y;
}

//---------------------------------------------------------------------------
//prop
inline bool JuiControl::IsVisible()
{
	return (m_nFlags & CTRL_FLAG_VISIBLE) != 0;
}

inline bool JuiControl::IsEnable()
{
	return (m_nFlags & CTRL_FLAG_ENABLE) != 0;
}

inline bool JuiControl::IsFocused()
{
	return (m_nFlags & CTRL_FLAG_FOCUSED) != 0;
}

inline bool JuiControl::IsMouseEnable()
{
	return (m_nFlags & CTRL_FLAG_MOUSE_ENABLE) != 0;
}

inline bool JuiControl::IsKeyboardEnable()
{
	return (m_nFlags & CTRL_FLAG_KEYBOARD_ENABLE) != 0;
}

inline bool JuiControl::IsContainer()
{
	return (m_nFlags & CTRL_FLAG_CONTAINER) != 0;
}

inline bool JuiControl::HasFlag(int flag)
{
	return (m_nFlags & flag) != 0;
}

inline void JuiControl::AddFlag(int flag)
{
	m_nFlags |= flag;
}

inline void JuiControl::RemoveFlag(int flag)
{
	m_nFlags &= ~flag;
}