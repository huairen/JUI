#ifndef JUI_DIALOG_H_
#define JUI_DIALOG_H_

#include "JuiWindow.h"

class JuiDialog : public JuiWindow
{
public:
	JuiDialog();
	~JuiDialog();

	bool Create(const char* title, int windowType, JuiWindow* parent = NULL);
	void EndDialog(int nResult);
	int Exec(JuiWindow* pParent = NULL);

protected:
	bool m_bModalFlag;
};

#endif