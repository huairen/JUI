#include "JuiTabBook.hxx"

JuiTabPage::JuiTabPage() : m_pTitle(0), m_pIconFile(0)
{
}

JuiTabPage::~JuiTabPage()
{
	delete m_pTitle;
	delete m_pIconFile;
}

//-----------------------------------------------------
JuiTabBook::JuiTabBook()
{
	m_nTabHeight = 30;
	m_pActivePage = NULL;
	m_pHoverTab = NULL;
}

JuiTabBook::~JuiTabBook()
{

}

bool JuiTabBook::LoadNormalImage( const char* filename )
{
	m_pNormalImage = sm_pRender->CreateImage(filename);
	if(m_pNormalImage != NULL)
	{
		m_nTabHeight = m_pNormalImage->GetHeight();
		return true;
	}
	return false;
}

bool JuiTabBook::LoadHighlightImage( const char* filename )
{
	m_pHighlightImage = sm_pRender->CreateImage(filename);
	return (m_pHighlightImage != NULL);
}

bool JuiTabBook::LoadPressImage( const char* filename )
{
	m_pPressImage = sm_pRender->CreateImage(filename);
	return (m_pPressImage != NULL);
}

void JuiTabBook::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	int nWidth;
	int nLeaveCount;

	JRectI tabRect;
	tabRect.position = offset;
	tabRect.extent.x = nWidth = GetWidth() / m_lsPages.GetCount();
	tabRect.extent.y = m_pNormalImage->GetHeight();

	nLeaveCount = GetWidth() % m_lsPages.GetCount();

	JuiTabPage* pTab = (JuiTabPage*)m_lsPages.First();
	while(pTab)
	{
		if(nLeaveCount > 0)
			tabRect.extent.x = nWidth + 1;
		else
			tabRect.extent.x = nWidth;

		JRectI clip = tabRect;
		if(clip.Intersect(rcPaint))
			RenderTab(clip, pTab);

		nLeaveCount -= 1;
		tabRect.position.x += tabRect.extent.x;
		pTab = (JuiTabPage*)m_lsPages.Next();
	}
}

void JuiTabBook::OnChildAdded( JuiControl *child )
{
	JuiTabPage *page = dynamic_cast<JuiTabPage*>(child);
	if(page != NULL)
	{
		m_lsPages.PushBack(page);

		JPoint2I pagePos = GetPosition();
		pagePos.y += m_nTabHeight;

		JPoint2I pageExtent = GetExtent();
		pageExtent.y -= m_nTabHeight;

		page->SetBounds(pagePos, pageExtent);
		page->SetVisible(false);

		if(m_pActivePage == NULL)
		{
			m_pActivePage = page;
			m_pActivePage->SetVisible(true);
		}
	}
}

void JuiTabBook::OnChildRemoved( JuiControl *child )
{
	m_lsPages.Pop(child);
}

void JuiTabBook::OnMouseLeave()
{
	if(m_pHoverTab != NULL)
	{
		SetUpdate();
		m_pHoverTab = NULL;
	}
}

void JuiTabBook::OnMouseDown( const MouseEventInfo& event )
{
	if(event.button != KEY_BUTTON0)
		return;

	JuiTabPage *pTab = FindHitTab(event.pos);
	if(pTab != NULL && m_pActivePage != pTab)
	{
		SetUpdate();
		if(m_pActivePage != NULL)
			m_pActivePage->SetVisible(false);

		m_pActivePage = pTab;

		if(m_pActivePage != NULL)
			m_pActivePage->SetVisible(true);
	}
}

void JuiTabBook::OnMouseMove( const MouseEventInfo& event )
{
	JuiTabPage *pTab = FindHitTab(event.pos);
	if(m_pHoverTab != pTab)
	{
		SetUpdate();
		m_pHoverTab = pTab;
	}
}



void JuiTabBook::RenderTab(const JRectI& tabRect, JuiTabPage *tab)
{
	if(tab == m_pActivePage)
		DrawImage(m_pPressImage, tabRect.position, tabRect, NULL, &tabRect);
	else if(tab == m_pHoverTab)
		DrawImage(m_pHighlightImage, tabRect.position, tabRect, NULL, &tabRect);
	else
		DrawImage(m_pNormalImage, tabRect.position, tabRect, NULL, &tabRect);
}

JuiTabPage * JuiTabBook::FindHitTab( const JPoint2I &pt )
{
	int nWidth = GetWidth() / m_lsPages.GetCount();
	int nLeaveCount = GetWidth() % m_lsPages.GetCount();

	JRectI tabRect;
	tabRect.position = GetPosition();
	tabRect.extent.y = m_nTabHeight;

	JuiTabPage* pTab = (JuiTabPage*)m_lsPages.First();
	while(pTab)
	{
		if(nLeaveCount > 0)
			tabRect.extent.x = nWidth + 1;
		else
			tabRect.extent.x = nWidth;

		if(tabRect.IsPointIn(pt))
			return pTab;

		nLeaveCount -= 1;
		tabRect.position.x += tabRect.extent.x;
		pTab = (JuiTabPage*)m_lsPages.Next();
	}

	return NULL;
}