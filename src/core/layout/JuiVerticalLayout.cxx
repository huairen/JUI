#include "JuiVerticalLayout.hxx"

JuiVerticalLayout::JuiVerticalLayout()
{
}

JuiVerticalLayout::~JuiVerticalLayout()
{
}

void JuiVerticalLayout::UpdateLayout( const JRectI& newRect )
{
	int nCount = m_lsChilds.GetCount();
	if(nCount == 0)
		return;

	int nWidth = newRect.size.x;
	int nHeight = newRect.size.y / nCount;
	int y = 0;
	int index = 1;

	JuiControl* pCom = (JuiControl*)m_lsChilds.First();
	while(pCom)
	{
		if(index == nCount)
			nHeight = newRect.size.y - y;

		pCom->SetBounds(0, y, nWidth, nHeight);
		y += nHeight;
		index++;

		pCom = (JuiControl*)m_lsChilds.Next();
	}
}
