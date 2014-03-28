#include "JuiLinearLayout.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiLinearLayout, JuiFrameLayout)

void JuiLinearLayout::UpdateLayout( const JRectI& newRect )
{
	int nCount = m_lsChilds.GetCount();
	if(nCount == 0)
		return;

	int nWidth = newRect.extent.x / nCount;
	int nHeight = newRect.extent.y;
	int x = 0;
	int index = 1;

	JuiControl* pCom = (JuiControl*)m_lsChilds.First();
	while(pCom)
	{
		if(index == nCount)
			nWidth = newRect.extent.x - x;

//		pCom->SetBounds(x, 0, nWidth, nHeight);
		x += nWidth;
		index++;

		pCom = (JuiControl*)m_lsChilds.Next();
	}
}
