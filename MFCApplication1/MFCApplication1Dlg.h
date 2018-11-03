
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic MY_PICTURE;
	void getCBitmapFade();
	void Ondraw(void);
	void FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin);
	afx_msg void OnBnClickedPre();
	afx_msg void OnBnClickedPlayCease();
	afx_msg void OnBnClickedNext();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedjiequ();
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedBlue();
	afx_msg void OnBnClickedGreen();
	afx_msg void OnBnClickedQuery();
};
