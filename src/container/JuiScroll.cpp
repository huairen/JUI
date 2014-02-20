#include "JuiScroll.h"

JuiScroll::JuiScroll()
{
	m_bAutoHide = false;
	m_bVertBar = true;
	m_bHorizBar = false;

	m_pBarImg = NULL;
}

JuiScroll::~JuiScroll()
{

}

void JuiScroll::LoadBarImage( const char* filename )
{
	m_pBarImg = sm_pRender->CreateTexture(filename);
}

void JuiScroll::LoadArrowImage( const char* filename )
{
	m_pArrowImg = sm_pRender->CreateTexture(filename);
}

void JuiScroll::OnMouseDown( const MouseEventInfo& event )
{

}

void JuiScroll::OnMouseUp( const MouseEventInfo& event )
{

}

void JuiScroll::OnMouseMove( const MouseEventInfo& event )
{

}

void JuiScroll::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	JRectI contentRect(offset, m_ptContentExtent);
	contentRect.Intersect(rcPaint);

	Parent::OnRender(offset, contentRect);

	if(m_bVertBar)
		DrawVScrollBar(offset, rcPaint);

	if(m_bHorizBar)
		DrawHScrollBar(offset, rcPaint);
}

void JuiScroll::UpdateLayout( const JRectI& newRect )
{
}

void JuiScroll::DrawVScrollBar( const JPoint2I &offset, const JRectI& rcPaint )
{
	JPoint2I pos = offset;
	if(m_pArrowImg != NULL)
	{
	}
}

void JuiScroll::DrawHScrollBar( const JPoint2I &offset, const JRectI& rcPaint )
{

}

bool JuiScroll::CalcChildExtent()
{
	if(m_lsChilds.GetCount() == 0)
		return false;

	JPoint2I maxPos(INT32_MIN, INT32_MIN);
	JPoint2I minPos(INT32_MAX, INT32_MAX);

	bool haveVisibleChild = false;
	JuiControl *ctrl = (JuiControl*)m_lsChilds.First();
	while(ctrl)
	{
		if(ctrl->IsVisible())
		{
			haveVisibleChild = true;

			minPos.x = GetMin(ctrl->GetPosition().x, minPos.x);
			minPos.y = GetMin(ctrl->GetPosition().y, minPos.y);

			JPoint2I ctrlMax = ctrl->GetPosition() + ctrl->GetExtent();

			maxPos.x = GetMax(ctrlMax.x, maxPos.x);
			maxPos.y = GetMax(ctrlMax.y, maxPos.y);
		}
		ctrl = (JuiControl*)m_lsChilds.Next();
	}

	if(!haveVisibleChild)
		return false;

	m_ptChildPos = minPos;
	m_ptChildExtent = maxPos - minPos;

	return true;
}
