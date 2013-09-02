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
		root->SetUpdateRegion(LocalToRoot(JPoint2I(0,0)), GetExtent());
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

void JuiControl::SetBounds(const JPoint2I& position, const JPoint2I& extent)
{
	m_rcBounds.extent = extent;
	m_rcBounds.position = position;
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
	JPoint2I newSize = GetExtent();

	int deltaX = newRect.extent.x - oldRect.extent.x;
	int deltaY = newRect.extent.y - oldRect.extent.y;

	switch (m_HorizAlign)
	{
	case CTRL_HORIZ_ALIGN_CENTER:
		newPosition.x = (newRect.extent.x - GetWidth()) >> 1;
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
		newPosition.y = (newRect.extent.y - GetHeight()) >> 1;
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
		srcRect.position -= offset;

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
			srcRect.position.x = (int)((rcPaint.position.x - offset.x) * xScale);
			srcRect.position.y = (int)((rcPaint.position.y - offset.y) * yScale);
			srcRect.extent.x = (int)(rcPaint.extent.x * xScale);
			srcRect.extent.y = (int)(rcPaint.extent.y * yScale);

			sm_pRender->DrawImageStretchSR(img, rcPaint, srcRect);
		}
		break;
	case CTRL_SCALE_CENTER:
		{
			JRectI DestRect = rcPaint;
			JRectI NextRect = rcPaint;

			for (int y = 0; y < 3; y++)
			{
				DestRect.position.x = NextRect.position.x;
				DestRect.extent.x = NextRect.extent.x;
				NextRect.position.y = DestRect.position.y;
				NextRect.extent.y = DestRect.extent.y;

				for (int x = 0; x < 3; x++)
				{
					DestRect.position.y = NextRect.position.y;
					DestRect.extent.y = NextRect.extent.y;

					DrawImageScaleCenter(img, offset, DestRect);

					if(DestRect.extent.x == 0)
						break;
				}

				if(DestRect.extent.y == 0)
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

	dstRect.position.x = rcPaint.position.x;
	dstRect.position.y = rcPaint.position.y;
	startPos = dstRect.position - offset;

	if(!xScale)
	{
		dstRect.extent.x = rcPaint.extent.x;
		srcRect.position.x = 0;
		srcRect.extent.x = dstRect.extent.x;
	}
	else if(startPos.x < imgHalfWidth)
	{
		dstRect.extent.x = GetMin(rcPaint.extent.x, imgHalfWidth - startPos.x);
		srcRect.position.x = (dstRect.position.x - offset.x);
		srcRect.extent.x = dstRect.extent.x;
	}
	else if(startPos.x < rightStart)
	{
		dstRect.extent.x = GetMin(rcPaint.extent.x, rightStart - startPos.x);
		srcRect.position.x = imgHalfWidth;
		srcRect.extent.x = 1;
	}
	else
	{
		dstRect.extent.x = rcPaint.extent.x;
		srcRect.position.x = startPos.x - (GetWidth() - img->GetWidth());
		srcRect.extent.x = dstRect.extent.x;
	}

	if(!yScale)
	{
		dstRect.extent.y = rcPaint.extent.y;
		srcRect.position.y = 0;
		srcRect.extent.y = dstRect.extent.y;
	}
	else if(startPos.y < imgHalfHeight)
	{
		dstRect.extent.y = GetMin(rcPaint.extent.y, imgHalfHeight - startPos.y);
		srcRect.position.y = (dstRect.position.y - offset.y);
		srcRect.extent.y = dstRect.extent.y;
	}
	else if(startPos.y < bottomStart)
	{
		dstRect.extent.y = GetMin(rcPaint.extent.y, bottomStart - startPos.y);
		srcRect.position.y = imgHalfHeight;
		srcRect.extent.y = 1;
	}
	else
	{
		dstRect.extent.y = rcPaint.extent.y;
		srcRect.position.y = startPos.y - (GetHeight() - img->GetHeight());
		srcRect.extent.y = dstRect.extent.y;
	}

	sm_pRender->DrawImageStretchSR(img, dstRect, srcRect);

	rcPaint.position.x += dstRect.extent.x;
	rcPaint.position.y += dstRect.extent.y;
	rcPaint.extent.x -= dstRect.extent.x;
	rcPaint.extent.y -= dstRect.extent.y;
}