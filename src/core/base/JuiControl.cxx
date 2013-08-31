#include "JuiControl.hxx"
#include "core/container/JuiContainer.hxx"


JRender* JuiControl::sm_pRender = NULL;

JuiControl::JuiControl() : m_nFlags(CTRL_FLAG_ENABLE | CTRL_FLAG_VISIBLE | CTRL_FLAG_MOUSE_ENABLE),
	m_HorizAlign(CTRL_HORIZ_ALIGN_LEFT), m_VerzAlign(CTRL_VERT_ALIGN_TOP), m_ScaleMode(CTRL_SCALE_CENTER),
	m_pParent(0), m_rcBounds(0,0,100,100), m_ptMinSize(8,2), m_ptMaxSize(-1,-1)
{
	m_szName[0] = 0;
}

JuiControl::~JuiControl()
{

}

JuiControl* JuiControl::GetRoot()
{
	JuiControl *root = NULL;
	JuiControl *parent = GetParent();

	while (parent)
	{
		root = parent;
		parent = parent->GetParent();
	}

	return root;
}

void JuiControl::SetUpdate()
{
	JuiControl *root = GetRoot();
	if(root != NULL)
		root->SetUpdateRegion(LocalToRoot(JPoint2I(0,0)), GetSize());
}

void JuiControl::MouseLock()
{
	JuiControl *root = GetRoot();
	if(!root)
		return;

	JuiInputManager *input = root->GetInputGenerator();
	if(input)
		input->MouseLock(this);
}

void JuiControl::MouseUnlock()
{
	JuiControl *root = GetRoot();
	if(!root)
		return;

	JuiInputManager *input = root->GetInputGenerator();
	if(input)
		input->MouseUnlock(this);
}

bool JuiControl::IsMouseLocked()
{
	JuiControl *root = GetRoot();
	if(!root)
		return false;

	JuiInputManager *input = root->GetInputGenerator();
	if(input)
		return input->GetMouseCaptureControl() == this;
	return false;
}

void JuiControl::SetBounds(const JPoint2I& point, const JPoint2I& size)
{
	m_rcBounds.size = size;
	m_rcBounds.point = point;
}

bool JuiControl::IsPointIn( const JPoint2I& pt )
{
	return m_rcBounds.IsPointIn(pt);
}

JPoint2I JuiControl::LocalToRoot( const JPoint2I &pos )
{
	JPoint2I ret = pos;
	ret += GetPosition();

	JuiControl* ptr = m_pParent;
	while(ptr)
	{
		ret += ptr->GetPosition();
		ptr = ptr->m_pParent;
	}

	return ret;
}

void JuiControl::OnParentResized( const JRectI &oldRect, const JRectI &newRect )
{
	JPoint2I newPosition = GetPosition();
	JPoint2I newSize = GetSize();

	int deltaX = newRect.size.x - oldRect.size.x;
	int deltaY = newRect.size.y - oldRect.size.y;

	switch (m_HorizAlign)
	{
	case CTRL_HORIZ_ALIGN_CENTER:
		newPosition.x = (newRect.size.x - GetWidth()) >> 1;
		break;
	case CTRL_HORIZ_ALIGN_RIGHT:
		newPosition.x += deltaX;
		break;
	case CTRL_HORIZ_ALIGN_WIDTH:
		newSize.x += deltaX;
		break;
	}

	switch (m_VerzAlign)
	{
	case CTRL_VERT_ALIGN_CENTER:
		newPosition.y = (newRect.size.y - GetHeight()) >> 1;
		break;
	case CTRL_VERT_ALIGN_BOTTOM:
		newPosition.y += deltaY;
		break;
	case CTRL_VERT_ALIGN_HEIGHT:
		newSize.y += deltaY;
		break;
	}

	SetBounds(newPosition, newSize);
}

void JuiControl::NotifySiblings( int message, int param )
{
	JuiContainer *parent = GetParent();
	if(parent == NULL)
		return;

	JuiControl *ctrl = parent->FirstChild();
	while(ctrl)
	{
		if(ctrl != this)
			ctrl->OnControlEvent(this, message, param);
		ctrl = parent->NextChild();
	}
}


void JuiControl::DrawImage( JImage* img, const JPoint2I &offset, const JRectI &rcPaint )
{
	if(img == NULL)
		return;

	//Í¼Æ¬²»Ëõ·Å
	if(img->GetWidth() == GetWidth() && img->GetHeight() == GetHeight())
	{
		JRectI srcRect = rcPaint;
		srcRect.point -= offset;

		sm_pRender->DrawImageStretchSR(img, rcPaint, srcRect);
		return;
	}

	switch(m_ScaleMode)
	{
	case CTRL_SCALE_ALL:
		{
			float xScale = (float)img->GetWidth() / GetWidth();
			float yScale = (float)img->GetHeight() / GetHeight();

			JRectI srcRect;
			srcRect.point.x = (int)((rcPaint.point.x - offset.x) * xScale);
			srcRect.point.y = (int)((rcPaint.point.y - offset.y) * yScale);
			srcRect.size.x = (int)(rcPaint.size.x * xScale);
			srcRect.size.y = (int)(rcPaint.size.y * yScale);

			sm_pRender->DrawImageStretchSR(img, rcPaint, srcRect);
		}
		break;
	case CTRL_SCALE_CENTER:
		{
			JRectI DestRect = rcPaint;
			JRectI NextRect = rcPaint;

			for (int y = 0; y < 3; y++)
			{
				DestRect.point.x = NextRect.point.x;
				DestRect.size.x = NextRect.size.x;
				NextRect.point.y = DestRect.point.y;
				NextRect.size.y = DestRect.size.y;

				for (int x = 0; x < 3; x++)
				{
					DestRect.point.y = NextRect.point.y;
					DestRect.size.y = NextRect.size.y;

					DrawImageScaleCenter(img, offset, DestRect);

					if(DestRect.size.x == 0)
						break;
				}

				if(DestRect.size.y == 0)
					break;
			}
		}
		break;
	case CTRL_SCALE_SIDE:
		{
		}
		break;
	}
}

void JuiControl::DrawImageScaleCenter( JImage* img, const JPoint2I &offset, JRectI &rcPaint )
{
	JRectI srcRect;
	JRectI dstRect;
	JPoint2I startPos;

	bool xScale = (img->GetWidth() != GetWidth());
	bool yScale = (img->GetHeight() != GetHeight());

	int imgHalfWidth = img->GetWidth() >> 1;
	int imgHalfHeight = img->GetHeight() >> 1;

	int rightStart = GetWidth() - imgHalfWidth;
	int bottomStart = GetHeight() - imgHalfHeight;

	dstRect.point.x = rcPaint.point.x;
	dstRect.point.y = rcPaint.point.y;
	startPos = dstRect.point - offset;

	if(!xScale)
	{
		dstRect.size.x = rcPaint.size.x;
		srcRect.point.x = 0;
		srcRect.size.x = dstRect.size.x;
	}
	else if(startPos.x < imgHalfWidth)
	{
		dstRect.size.x = GetMin(rcPaint.size.x, imgHalfWidth - startPos.x);
		srcRect.point.x = (dstRect.point.x - offset.x);
		srcRect.size.x = dstRect.size.x;
	}
	else if(startPos.x < rightStart)
	{
		dstRect.size.x = GetMin(rcPaint.size.x, rightStart - startPos.x);
		srcRect.point.x = imgHalfWidth;
		srcRect.size.x = 1;
	}
	else
	{
		dstRect.size.x = rcPaint.size.x;
		srcRect.point.x = startPos.x - (GetWidth() - img->GetWidth());
		srcRect.size.x = dstRect.size.x;
	}

	if(!yScale)
	{
		dstRect.size.y = rcPaint.size.y;
		srcRect.point.y = 0;
		srcRect.size.y = dstRect.size.y;
	}
	else if(startPos.y < imgHalfHeight)
	{
		dstRect.size.y = GetMin(rcPaint.size.y, imgHalfHeight - startPos.y);
		srcRect.point.y = (dstRect.point.y - offset.y);
		srcRect.size.y = dstRect.size.y;
	}
	else if(startPos.y < bottomStart)
	{
		dstRect.size.y = GetMin(rcPaint.size.y, bottomStart - startPos.y);
		srcRect.point.y = imgHalfHeight;
		srcRect.size.y = 1;
	}
	else
	{
		dstRect.size.y = rcPaint.size.y;
		srcRect.point.y = startPos.y - (GetHeight() - img->GetHeight());
		srcRect.size.y = dstRect.size.y;
	}

	sm_pRender->DrawImageStretchSR(img, dstRect, srcRect);

	rcPaint.point.x += dstRect.size.x;
	rcPaint.point.y += dstRect.size.y;
	rcPaint.size.x -= dstRect.size.x;
	rcPaint.size.y -= dstRect.size.y;
}