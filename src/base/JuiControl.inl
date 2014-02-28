
inline void JuiControl::SetName(const char* name)
{
	m_Name = name;
}

inline void JuiControl::SetParent( JuiContainer* control )
{
	m_pParent = control;
}

inline JuiContainer*  JuiControl::GetParent()
{
	return m_pParent;
}

inline const char* JuiControl::GetName()
{
	return m_Name.c_str();
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
	return (m_nFlags & FLAG_VISIBLE) != 0;
}

inline bool JuiControl::IsEnable() const
{
	return (m_nFlags & FLAG_ENABLE) != 0;
}

inline bool JuiControl::IsFocused() const
{
	return (m_nFlags & FLAG_FOCUSED) != 0;
}

inline bool JuiControl::IsMouseEnable() const
{
	return (m_nFlags & FLAG_MOUSE_ENABLE) != 0;
}

inline bool JuiControl::IsKeyboardEnable() const
{
	return (m_nFlags & FLAG_KEYBOARD_ENABLE) != 0;
}

inline bool JuiControl::IsContainer() const
{
	return (m_nFlags & FLAG_CONTAINER) != 0;
}

inline bool JuiControl::HasFlag(int flag) const
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