#include "JStateListDrawable.h"
#include "Graphics/JRenderSystem.h"

JStateListDrawable::JStateListDrawable()
	: m_pCurrDrawable(0)
{

}

JStateListDrawable::~JStateListDrawable()
{
	for (int i=0; i<m_DrawableList.GetCount(); ++i)
		delete m_DrawableList.At(i);
}

uint32_t JStateListDrawable::GetWidth()
{
	if(!m_DrawableList.IsEmpty())
		return m_DrawableList.First()->GetWidth();
	return 0;
}

uint32_t JStateListDrawable::GetHeight()
{
	if(!m_DrawableList.IsEmpty())
		return m_DrawableList.First()->GetHeight();
	return 0;
}

void JStateListDrawable::Draw(const JRectI& rcOrigin, const JRectI& rcPaint)
{
	if(m_pCurrDrawable != NULL)
		m_pCurrDrawable->Draw(rcOrigin, rcPaint);
}

void JStateListDrawable::SetState(int nState)
{
	if(nState < m_DrawableList.GetCount())
		m_pCurrDrawable = m_DrawableList.At(nState);
}

void JStateListDrawable::Add(JDrawable* pDrawable, int nState)
{
	if(m_pCurrDrawable == NULL)
		m_pCurrDrawable = pDrawable;

	m_DrawableList.PushBack(pDrawable);
}

