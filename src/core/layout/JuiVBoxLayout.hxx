#ifndef JUI_VBOXLAYOUT_H_
#define JUI_VBOXLAYOUT_H_

#include "core/container/JuiContainer.hxx"

class JuiVBoxLayout : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiVBoxLayout();
	~JuiVBoxLayout();

	virtual void UpdateLayout(const JRectI& newRect);

protected:

};

#endif