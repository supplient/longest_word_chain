
// MFCUIDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "MFCUIDlg.h"
#include "afxdialogex.h"

#include "../Core/Core.h"
#include "../UIUtility/UIUtility.h"

#include <string>
#include <fstream>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCUIDlg 对话框



CMFCUIDlg::CMFCUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCUI_DIALOG, pParent)
	, m_wc_radio(0)
	, m_input_file(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_w, m_wc_radio);
	DDX_Radio(pDX, IDC_RADIO_input_hand, m_input_file);
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
	ON_BN_CLICKED(IDC_RADIO_input_hand, &CMFCUIDlg::OnBnClickedRadioinputhand)
	ON_BN_CLICKED(IDC_RADIO_input_file, &CMFCUIDlg::OnBnClickedRadioinputhand)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CMFCUIDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_OPEN, &CMFCUIDlg::OnBnClickedButtonExportOpen)
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
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||"); 
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
	wchar_t c = str.GetAt(0);
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
	wchar_t c = str.GetAt(0);
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

	// Load Input
	char **words;
	unsigned int len;
	// Check input method
	if (m_input_file) {
		// Get & Check path
		CString str_path;
		((CEdit*)GetDlgItem(IDC_EDIT_PATH))->GetWindowTextW(str_path);
		if (str_path.GetLength() < 1) {
			callWarningBox(L"Must input a file path.");
			return;
		}
		// Read File
		try {
			FileReader reader;
			words = reader.read(std::string(CW2A(str_path.GetString())));
			len = reader.getReadLen();
		}
		catch (std::string e) {
			callWarningBox(CString(e.c_str()));
			return;
		}
	}
	else {
		// Get input
		CString str_input;
		((CEdit*)GetDlgItem(IDC_EDIT_input))->GetWindowTextW(str_input);
		
		// NOTE We allow empty string as input

		// Process Input
		try {
			StreamReader reader;
			std::istringstream str_in(std::string(CW2A(str_input.GetString())));
			words = reader.read(str_in);
			len = reader.getReadLen();
		}
		catch (std::string e) {
			callWarningBox(CString(e.c_str()));
			return;
		}
	}

	// Get & Check h,t
	bool use_h;
	bool use_t;
	wchar_t char_h = 0;
	wchar_t char_t = 0;
	
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

	// Call Core
	char** res = new char*[MAX_WORD_NUM + 1];
	int res_len;
	try {
		if (max_char) {
			res_len = Core::gen_chain_char(
				words, len, res,
				(char)char_h, (char)char_t,
				enable_loop
			);
		}
		else {
			res_len = Core::gen_chain_word(
				words, len, res,
				(char)char_h, (char)char_t,
				enable_loop
			);
		}
	}
	catch (std::string e) {
		callWarningBox(CString(e.c_str()));
		delete[] res;
		return;
	}

	// Update output show control
	CString str_output;
	for (int i = 0; i < res_len; i++) {
		str_output.Append(CString(res[i]));
		str_output.Append(L"\r\n");
	}
	((CEdit*)GetDlgItem(IDC_EDIT_output))->SetWindowTextW(str_output);

	delete[] res;
}

void CMFCUIDlg::OnBnClickedRadioinputhand()
{
	UpdateData(TRUE);
	if (m_input_file) {
		GetDlgItem(IDC_EDIT_PATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_input)->EnableWindow(FALSE);
	}
	else {
		GetDlgItem(IDC_EDIT_PATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_input)->EnableWindow(TRUE);
	}
}


void CMFCUIDlg::OnBnClickedButtonExport()
{
	// Get Path
	CString c_output_path;
	((CEdit*)GetDlgItem(IDC_EDIT_EXPORT_PATH))->GetWindowTextW(c_output_path);

	// Output result to File
	std::string output_path(CW2A(c_output_path.GetString()));
	std::ofstream ofs(output_path);
	if (!ofs.is_open()) {
		callWarningBox(
			L"Open " + CString(output_path.c_str()) + L" failed.");
		return;
	}

	CString str_output;
	((CEdit*)GetDlgItem(IDC_EDIT_output))->GetWindowTextW(str_output);
	ofs << std::string(CW2A(str_output.GetString()));

	ofs.close();

	// Notice user.
	MessageBox(L"Has exported to " + CString(output_path.c_str()));
}



void CMFCUIDlg::OnBnClickedButtonExportOpen()
{
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||"); 
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_EXPORT_PATH, strFilePath);
	}
}
