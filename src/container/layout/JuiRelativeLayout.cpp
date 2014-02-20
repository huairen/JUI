#include "JuiRelativeLayout.h"

JuiRelativeLayout::JuiRelativeLayout()
{
}

JuiRelativeLayout::~JuiRelativeLayout()
{
}

void JuiRelativeLayout::UpdateLayout( const JRectI& newRect )
{
	int nCount = m_lsChilds.GetCount();
	if(nCount == 0)
		return;

	int nWidth = newRect.extent.x;
	int nHeight = newRect.extent.y / nCount;
	int y = 0;
	int index = 1;

	JuiControl* pCom = (JuiControl*)m_lsChilds.First();
	while(pCom)
	{
		if(index == nCount)
			nHeight = newRect.extent.y - y;

		pCom->SetBounds(0, y, nWidth, nHeight);
		y += nHeight;
		index++;

		pCom = (JuiControl*)m_lsChilds.Next();
	}
}
