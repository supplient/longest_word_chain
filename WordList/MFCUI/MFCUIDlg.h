﻿
// MFCUIDlg.h: 头文件
//

#pragma once


// CMFCUIDlg 对话框
class CMFCUIDlg : public CDialogEx
{
// 构造
public:
	CMFCUIDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio_wc();
	INT m_wc_radio;
	afx_msg void OnBnClickedCheckh();
	afx_msg void OnBnClickedCheckt();
	afx_msg void OnEnUpdateEdith();
	afx_msg void OnEnUpdateEditt();
	afx_msg void OnBnClickedOk();

private:
	void callWarningBox(LPCTSTR str);
public:
	afx_msg void OnEnChangeEdith();
};
