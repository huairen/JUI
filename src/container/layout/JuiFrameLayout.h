#ifndef JUI_FRAMELAYOUT_H_
#define JUI_FRAMELAYOUT_H_

struct Bound
{
	int left;
	int top;
	int right;
	int bottom;
};

class JuiLayoutParameter
{
public:
	enum LayoutSizeType
	{
		SIZE_CUSTOM,
		SIZE_FILL_PARENT,
		SIZE_WRAP_CONTENT,
	};

private:
	LayoutSizeType m_LayoutWidth;
	LayoutSizeType m_LayoutHeight;
	Bound m_Margin;
};

#endif