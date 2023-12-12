// CAngleInputDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProc_20190829.h"
#include "afxdialogex.h"
#include "CAngleInputDialog.h"


// CAngleInputDialog 대화 상자

IMPLEMENT_DYNAMIC(CAngleInputDialog, CDialogEx)

CAngleInputDialog::CAngleInputDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_iAngle(0)
{

	m_iAngle = 0;
}

CAngleInputDialog::~CAngleInputDialog()
{
}

void CAngleInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDD_DIALOG1, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleInputDialog, CDialogEx)
//	ON_COMMAND(IDC_STATIC, &CAngleInputDialog::IDC_STATIC1)
END_MESSAGE_MAP()
