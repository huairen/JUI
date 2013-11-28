#include "JuiRollout.hxx"

JuiRollout::JuiRollout()
{
}

JuiRollout::~JuiRollout()
{

}

void JuiRollout::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	offset.y += m_nBarHeight;
}