
// HttpClientDemoDlg.h : ͷ�ļ�
//

#pragma once


// CHttpClientDemoDlg �Ի���
class CHttpClientDemoDlg : public CDialogEx
{
// ����
public:
	CHttpClientDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HTTPCLIENTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGet();
	afx_msg void OnBnClickedPost();
	afx_msg void OnBnClickedQuery();
};
