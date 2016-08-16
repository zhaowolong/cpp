
// HttpClientDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpClientDemo.h"
#include "HttpClientDemoDlg.h"
#include "afxdialogex.h"
#include "HttpClient.h"
#include "jsoncpp/json.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace Json;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHttpClientDemoDlg 对话框



CHttpClientDemoDlg::CHttpClientDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHttpClientDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpClientDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpClientDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET, &CHttpClientDemoDlg::OnBnClickedGet)
	ON_BN_CLICKED(IDC_POST, &CHttpClientDemoDlg::OnBnClickedPost)
	ON_BN_CLICKED(IDC_QUERY, &CHttpClientDemoDlg::OnBnClickedQuery)
END_MESSAGE_MAP()


// CHttpClientDemoDlg 消息处理程序

BOOL CHttpClientDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHttpClientDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHttpClientDemoDlg::OnPaint()
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
HCURSOR CHttpClientDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpClientDemoDlg::OnBnClickedGet()
{
	// TODO: 在此添加控件通知处理程序代码
	CHttpClient httpClient;
	CString strRes;
	httpClient.HttpGet(TEXT("http://14.17.104.56:6782/httpInsert"), TEXT("{\"a\":\"1\"}"), strRes);
	MessageBox(strRes);
}


void CHttpClientDemoDlg::OnBnClickedPost()
{
	// TODO: 在此添加控件通知处理程序代码
	CHttpClient httpClient;
	CString strRes;
	CString strSend;
	strSend.Format(TEXT("{\"userId\":%d,\"account\":\"%s\",\"nickName\":\"%s\",\"fanShu\":%d}"), 2, TEXT("zwlong"), TEXT("rucizhizhuo"), 5);
	httpClient.HttpPost(TEXT("http://14.17.104.56:6782/httpInsert"), strSend, strRes);
	std::string strValue = "{\"name\":\"赵臣民测试\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";

	Json::Reader reader;
	Json::Value value;


	if (reader.parse(strValue, value))
	{
		string out = value["name"].asString();
	}
	MessageBox(strRes);
}


void CHttpClientDemoDlg::OnBnClickedQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	CHttpClient httpClient;
	CString strRes;
	CString strSend;
	strSend.Format(TEXT("{\"rankType\":%d}"), 2);
	httpClient.HttpPost(TEXT("http://14.17.104.56:6782/httpRank"), strSend, strRes);

	MessageBox(strRes);
}
