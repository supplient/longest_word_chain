
// MFCUIDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "MFCUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCUIDlg 对话框



CMFCUIDlg::CMFCUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCUI_DIALOG, pParent)
	, m_wc_radio(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_w, m_wc_radio);
}

BEGIN_MESSAGE_MAP(CMFCUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCUIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO_w, &CMFCUIDlg::OnBnClickedRadio_wc)
	ON_BN_CLICKED(IDC_RADIO_c, &CMFCUIDlg::OnBnClickedRadio_wc)
	ON_BN_CLICKED(IDC_CHECK_h, &CMFCUIDlg::OnBnClickedCheckh)
	ON_BN_CLICKED(IDC_CHECK_t, &CMFCUIDlg::OnBnClickedCheckt)
	ON_EN_UPDATE(IDC_EDIT_h, &CMFCUIDlg::OnEnUpdateEdith)
	ON_EN_UPDATE(IDC_EDIT_t, &CMFCUIDlg::OnEnUpdateEditt)
	ON_BN_CLICKED(IDOK, &CMFCUIDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_h, &CMFCUIDlg::OnEnChangeEdith)
END_MESSAGE_MAP()


// CMFCUIDlg 消息处理程序

BOOL CMFCUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCUIDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH, strFilePath);
	}
}


void CMFCUIDlg::OnBnClickedRadio_wc()
{
	UpdateData(TRUE);
}


void CMFCUIDlg::OnBnClickedCheckh()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_h);
	int state = pBtn->GetCheck();

	switch (state) {
	case 0: 
		GetDlgItem(IDC_EDIT_h)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_EDIT_h)->EnableWindow(TRUE);
		break;
	default:
		GetDlgItem(IDC_EDIT_h)->EnableWindow(FALSE);
	}
}


void CMFCUIDlg::OnBnClickedCheckt()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_t);
	int state = pBtn->GetCheck();

	switch (state) {
	case 0: 
		GetDlgItem(IDC_EDIT_t)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_EDIT_t)->EnableWindow(TRUE);
		break;
	default:
		GetDlgItem(IDC_EDIT_t)->EnableWindow(FALSE);
	}
}



void CMFCUIDlg::OnEnUpdateEdith()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_h);
	CString str;
	pEdit->GetWindowTextW(str);

	// check length
	if (str.GetLength() < 1)
		return;
	if (str.GetLength() > 1) {
		str = str.GetAt(str.GetLength() - 1);
		pEdit->SetWindowTextW(str);
	}

	// check alpha
	char c = str.GetAt(0);
	if (!(c >= 'a' && c <= 'z')) {
		// not alpha
		pEdit->SetWindowTextW(L"");
	}
	else
		pEdit->SetSel(1, 1, FALSE);
}


void CMFCUIDlg::OnEnUpdateEditt()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_t);
	CString str;
	pEdit->GetWindowTextW(str);

	// check length
	if (str.GetLength() < 1)
		return;
	if (str.GetLength() > 1) {
		str = str.GetAt(str.GetLength() - 1);
		pEdit->SetWindowTextW(str);
	}

	// check alpha
	char c = str.GetAt(0);
	if (!(c >= 'a' && c <= 'z')) {
		// not alpha
		pEdit->SetWindowTextW(L"");
	}
	else
		pEdit->SetSel(1, 1, FALSE);
}

void CMFCUIDlg::callWarningBox(LPCTSTR str) {
	MessageBoxW(str, L"Warning", MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
}

void CMFCUIDlg::OnBnClickedOk()
{
	// Get & Check path
	CString str_path;
	((CEdit*)GetDlgItem(IDC_EDIT_PATH))->GetWindowTextW(str_path);
	if (str_path.GetLength() < 1) {
		callWarningBox(L"Must input a file path.");
		return;
	}

	// Get & Check h,t
	bool use_h;
	bool use_t;
	char char_h;
	char char_t;
	
	use_h = ((CButton*)GetDlgItem(IDC_CHECK_h))->GetCheck();
	use_t = ((CButton*)GetDlgItem(IDC_CHECK_t))->GetCheck();
	if (use_h) {
		CString str_temp;
		((CEdit*)GetDlgItem(IDC_EDIT_h))->GetWindowTextW(str_temp);
		if (str_temp.GetLength() < 1) {
			callWarningBox(L"-h is set, so you must assign a char as head.");
			return;
		}
		char_h = str_temp.GetAt(0);
	}
	if (use_t) {
		CString str_temp;
		((CEdit*)GetDlgItem(IDC_EDIT_t))->GetWindowTextW(str_temp);
		if (str_temp.GetLength() < 1) {
			callWarningBox(L"-t is set, so you must assign a char as tail.");
			return;
		}
		char_t = str_temp.GetAt(0);
	}

	// Get w/c
	bool max_char;
	switch (m_wc_radio) {
	case 0:
		max_char = false;
		break;
	case 1:
		max_char = true;
		break;
	}
	if (m_wc_radio)
		max_char = true;
	else
		max_char = false;

	// Get r
	bool enable_loop;
	enable_loop = ((CButton*)GetDlgItem(IDC_CHECK_r))->GetCheck();

	// TODO output the command for user to check
}


void CMFCUIDlg::OnEnChangeEdith()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

