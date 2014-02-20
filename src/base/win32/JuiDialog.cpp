#include "JuiDialog.h"

JuiDialog::JuiDialog()
{
	m_bModalFlag = false;
}

JuiDialog::~JuiDialog()
{

}

bool JuiDialog::Create(const char* title, int windowType, JuiWindow* parent /*= NULL*/)
{
//	::CreateDialog(NULL,title,parent ? parent->GetHander() : NULL, JuiWindow::WndProc);
	return true;
}

void JuiDialog::EndDialog(int nResult)
{
	if(::IsWindow(m_hWnd))
	{
		if(m_bModalFlag)
			::EndDialog(m_hWnd,nResult);
		else
			::DestroyWindow(m_hWnd);
	}
}

int JuiDialog::Exec(JuiWindow* pParent /*= NULL*/)
{
	m_pParent = pParent;

	m_bModalFlag = true;
 	int result = 0;//::DialogBox(NULL, MAKEINTRESOURCE(m_nResID),
// 		m_pParent ? m_pParent->GetHander() : NULL, (DLGPROC)JuiWindow::WinProc);
	m_bModalFlag = false;

	return result;
}

