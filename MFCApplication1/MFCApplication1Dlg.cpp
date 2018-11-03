
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "cv.h"
#include "highgui.h"
#include "string"
#include"fstream"
#include"omp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MAX_COUNT 6 // 例如在资源中创建13张bmp图片,ID号连续
// 成员变量
int nIndex = 0;			//当前图片编号
CBitmap bmps[MAX_COUNT];//6张图片所在数组
CBitmap bitmap;			//显示图片
int type = 0;          //用来判断是否暂停播放
int m = 0, n = 0;     //表示淡入淡出出中的图片下标
CString ma;
int fade_value = 0;
int count = 0;	//计数 延长fade_value显示时间
int fadeType = 0;		//淡入淡出效果类型  0为淡出 1为淡入
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PICTURE, MY_PICTURE);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_PRE, &CMFCApplication1Dlg::OnBnClickedPre)
	ON_BN_CLICKED(ID_PLAY_CEASE, &CMFCApplication1Dlg::OnBnClickedPlayCease)
	ON_BN_CLICKED(ID_NEXT, &CMFCApplication1Dlg::OnBnClickedNext)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_jiequ, &CMFCApplication1Dlg::OnBnClickedjiequ)
	ON_BN_CLICKED(ID_QUERY, &CMFCApplication1Dlg::OnBnClickedQuery)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	nIndex = 0;

	bitmap.LoadBitmap(IDB_BITMAP1);
	//使用一样大的bmp图片
	bmps[0].LoadBitmap(IDB_BITMAP1);
	bmps[1].LoadBitmap(IDB_BITMAP2);
	bmps[2].LoadBitmap(IDB_BITMAP3);
	bmps[3].LoadBitmap(IDB_BITMAP4);
	bmps[4].LoadBitmap(IDB_BITMAP5);
	bmps[5].LoadBitmap(IDB_BITMAP6);
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedPre()//上一张
{
	// TODO:  在此添加控件通知处理程序代码
	type = 1;
	KillTimer(1);
	ma = "开始自动播放";
	GetDlgItem(ID_PLAY_CEASE)->SetWindowText(ma);
	m = nIndex;
	nIndex--;//顺序显示
	if (nIndex == -1)//处理溢出现象
		nIndex = MAX_COUNT - 1;
	n = nIndex;
	getCBitmapFade();//图片淡入淡出函数
}


void CMFCApplication1Dlg::OnBnClickedPlayCease()//播放或者暂停
{
	// TODO:  在此添加控件通知处理程序代码
	CString ma;
	switch (type){
	case 0:
		SetTimer(1, 1000, NULL);
		ma = "停止自动播放";
		GetDlgItem(ID_PLAY_CEASE)->SetWindowText(ma);
		type = 1;
		break;

	case 1:
		KillTimer(1);
		ma = "开始自动播放";
		GetDlgItem(ID_PLAY_CEASE)->SetWindowText(ma);
		type = 0;
		break;
	}
}


void CMFCApplication1Dlg::OnBnClickedNext()//下一张
{
	// TODO:  在此添加控件通知处理程序代码
	type = 1;
	KillTimer(1);
	ma = "开始自动播放";
	GetDlgItem(ID_PLAY_CEASE)->SetWindowText(ma);
	m = nIndex;
	nIndex++;//顺序显示
	if (nIndex == MAX_COUNT)
		nIndex = 0;//处理溢出现象
	n = nIndex;
	getCBitmapFade();//图片淡入淡出函数
}
void CMFCApplication1Dlg::getCBitmapFade(){//实现淡入淡出
	BITMAP b;
	bmps[m].GetBitmap(&b);
	int size = b.bmHeight*b.bmWidthBytes;//b.bmWidthBytes代表每行有多少个字节，b.bmWidth每行有多少个像素点
	BYTE *lpBits1 = new BYTE[size];
	bmps[m].GetBitmapBits(size, lpBits1);//得到图片的字节数组，也就是每个像素点转换成四个字节
	BITMAP c;
	int x = 0;
	bmps[n].GetBitmap(&c);
	BYTE *lpBits2 = new BYTE[size];
	bmps[n].GetBitmapBits(size, lpBits2);
	int bPixel = b.bmBitsPixel / 8;
	BYTE *lpBits3 = new BYTE[size];

	BYTE *pic1 = new BYTE[8];
	BYTE *pic2 = new BYTE[8];
	BYTE *pic3 = new BYTE[8];
	BYTE *pic4 = new BYTE[8];
	BYTE *pic5 = new BYTE[8];
	BYTE *pic6 = new BYTE[8];
	int *rgb = new int[6];
	for (int fade = 127; fade >= 0; fade--)
	{
		for (int y = 0; y < b.bmHeight; y++)
		{
			#pragma omp parallel for num_threads(3) private(x)//3线程并行计算
			for (int x = 0; x < b.bmWidth; x = x + 6) //3个两像素同时计算
			{
				rgb[0] = y*b.bmWidthBytes + x * 4;//用于存储中间结果，每个像素点四个字节，表示每个字节的起始位置，取6个像素点
				rgb[1] = y*b.bmWidthBytes + (x + 1) * 4;
				rgb[2] = y*b.bmWidthBytes + (x + 2) * 4;
				rgb[3] = y*b.bmWidthBytes + (x + 3) * 4;
				rgb[4] = y*b.bmWidthBytes + (x + 4) * 4;
				rgb[5] = y*b.bmWidthBytes + (x + 5) * 4;
				//A图两个像素8字节
				pic1[0] = lpBits1[rgb[0]];
				pic1[1] = lpBits1[rgb[0] + 1];
				pic1[2] = lpBits1[rgb[0] + 2];
				pic1[3] = lpBits1[rgb[0] + 3];
				pic1[4] = lpBits1[rgb[1]];
				pic1[5] = lpBits1[rgb[1] + 1];
				pic1[6] = lpBits1[rgb[1] + 2];
				pic1[7] = lpBits1[rgb[1] + 3];
				//B图两个像素8字节
				pic2[0] = lpBits2[rgb[0]];
				pic2[1] = lpBits2[rgb[0] + 1];
				pic2[2] = lpBits2[rgb[0] + 2];
				pic2[3] = lpBits2[rgb[0] + 3];
				pic2[4] = lpBits2[rgb[1]];
				pic2[5] = lpBits2[rgb[1] + 1];
				pic2[6] = lpBits2[rgb[1] + 2];
				pic2[7] = lpBits2[rgb[1] + 3];

				//A图两个像素8字节
				pic3[0] = lpBits1[rgb[2]];
				pic3[1] = lpBits1[rgb[2] + 1];
				pic3[2] = lpBits1[rgb[2] + 2];
				pic3[3] = lpBits1[rgb[2] + 3];
				pic3[4] = lpBits1[rgb[3]];
				pic3[5] = lpBits1[rgb[3] + 1];
				pic3[6] = lpBits1[rgb[3] + 2];
				pic3[7] = lpBits1[rgb[3] + 3];
				//B图两个像素8字节
				pic4[0] = lpBits2[rgb[2]];
				pic4[1] = lpBits2[rgb[2] + 1];
				pic4[2] = lpBits2[rgb[2] + 2];
				pic4[3] = lpBits2[rgb[2] + 3];
				pic4[4] = lpBits2[rgb[3]];
				pic4[5] = lpBits2[rgb[3] + 1];
				pic4[6] = lpBits2[rgb[3] + 2];
				pic4[7] = lpBits2[rgb[3] + 3];


				//A图两个像素8字节
				pic5[0] = lpBits1[rgb[4]];
				pic5[1] = lpBits1[rgb[4] + 1];
				pic5[2] = lpBits1[rgb[4] + 2];
				pic5[3] = lpBits1[rgb[4] + 3];
				pic5[4] = lpBits1[rgb[5]];
				pic5[5] = lpBits1[rgb[5] + 1];
				pic5[6] = lpBits1[rgb[5] + 2];
				pic5[7] = lpBits1[rgb[5] + 3];
				//B图两个像素8字节
				pic6[0] = lpBits2[rgb[4]];
				pic6[1] = lpBits2[rgb[4] + 1];
				pic6[2] = lpBits2[rgb[4] + 2];
				pic6[3] = lpBits2[rgb[4] + 3];
				pic6[4] = lpBits2[rgb[5]];
				pic6[5] = lpBits2[rgb[5] + 1];
				pic6[6] = lpBits2[rgb[5] + 2];
				pic6[7] = lpBits2[rgb[5] + 3];


				__m128i xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6;
				__m128i xmm8 = _mm_setzero_si128();
				xmm0 = _mm_set_epi16(fade, fade, fade, fade, fade, fade, fade, fade);//8个fade因子装入寄存器
				xmm1 = _mm_loadu_si128((__m128i*)pic1);//A的2个像素分量装入寄存器
				xmm1 = _mm_unpacklo_epi8(xmm1, xmm8);  //8个一位解紧缩至16位
				xmm2 = _mm_loadu_si128((__m128i*)pic2);//B的2个像素分量装入寄存器
				xmm2 = _mm_unpacklo_epi8(xmm2, xmm8);  //8个一位解紧缩
				xmm1 = _mm_sub_epi16(xmm1, xmm2);       //A减B
				xmm1 = _mm_mullo_epi16(xmm1, xmm0);//乘法
				xmm1 = _mm_srai_epi16(xmm1, 7);//右移7位
				xmm1 = _mm_add_epi16(xmm1, xmm2);//加法+B
				xmm1 = _mm_packus_epi16(xmm1, xmm8);//16个一位紧缩
				lpBits3[rgb[0]] = _mm_extract_epi8(xmm1, 0);//依次提取每个整型
				lpBits3[rgb[0] + 1] = _mm_extract_epi8(xmm1, 1);
				lpBits3[rgb[0] + 2] = _mm_extract_epi8(xmm1, 2);
				lpBits3[rgb[0] + 3] = _mm_extract_epi8(xmm1, 3);
				lpBits3[rgb[1]] = _mm_extract_epi8(xmm1, 4);
				lpBits3[rgb[1] + 1] = _mm_extract_epi8(xmm1, 5);
				lpBits3[rgb[1] + 2] = _mm_extract_epi8(xmm1, 6);
				lpBits3[rgb[1] + 3] = _mm_extract_epi8(xmm1, 7);

				xmm3 = _mm_loadu_si128((__m128i*)pic3);
				xmm3 = _mm_unpacklo_epi8(xmm3, xmm8);  //A的2个像素分量装入寄存器
				xmm4 = _mm_loadu_si128((__m128i*)pic4);
				xmm4 = _mm_unpacklo_epi8(xmm4, xmm8);  //B的2个像素分量装入寄存器
				xmm3 = _mm_sub_epi16(xmm3, xmm4);       //A减B
				xmm3 = _mm_mullo_epi16(xmm3, xmm0);//乘法
				xmm3 = _mm_srai_epi16(xmm3, 7);//右移7位
				xmm3 = _mm_add_epi16(xmm3, xmm4);//加法
				xmm3 = _mm_packus_epi16(xmm3, xmm8);//压缩
				lpBits3[rgb[2]] = _mm_extract_epi8(xmm3, 0);//依次提取每个整型
				lpBits3[rgb[2] + 1] = _mm_extract_epi8(xmm3, 1);
				lpBits3[rgb[2] + 2] = _mm_extract_epi8(xmm3, 2);
				lpBits3[rgb[2] + 3] = _mm_extract_epi8(xmm3, 3);
				lpBits3[rgb[3]] = _mm_extract_epi8(xmm3, 4);
				lpBits3[rgb[3] + 1] = _mm_extract_epi8(xmm3, 5);
				lpBits3[rgb[3] + 2] = _mm_extract_epi8(xmm3, 6);
				lpBits3[rgb[3] + 3] = _mm_extract_epi8(xmm3, 7);

				xmm5 = _mm_loadu_si128((__m128i*)pic5);
				xmm5 = _mm_unpacklo_epi8(xmm5, xmm8);  //A的2个像素分量装入寄存器
				xmm6 = _mm_loadu_si128((__m128i*)pic6);
				xmm6 = _mm_unpacklo_epi8(xmm6, xmm8);  //B的2个像素分量装入寄存器
				xmm5 = _mm_sub_epi16(xmm5, xmm6);       //A减B
				xmm5 = _mm_mullo_epi16(xmm5, xmm0);//乘法
				xmm5 = _mm_srai_epi16(xmm5, 7);//右移7位
				xmm5 = _mm_add_epi16(xmm5, xmm6);//加法
				xmm5 = _mm_packus_epi16(xmm5, xmm8);//压缩
				lpBits3[rgb[4]] = _mm_extract_epi8(xmm5, 0);//依次提取每个整型
				lpBits3[rgb[4] + 1] = _mm_extract_epi8(xmm5, 1);
				lpBits3[rgb[4] + 2] = _mm_extract_epi8(xmm5, 2);
				lpBits3[rgb[4] + 3] = _mm_extract_epi8(xmm5, 3);
				lpBits3[rgb[5]] = _mm_extract_epi8(xmm5, 4);
				lpBits3[rgb[5] + 1] = _mm_extract_epi8(xmm5, 5);
				lpBits3[rgb[5] + 2] = _mm_extract_epi8(xmm5, 6);
				lpBits3[rgb[5] + 3] = _mm_extract_epi8(xmm5, 7);
			}
		}
		bitmap.SetBitmapBits(size, lpBits3);
		Ondraw();
	}
	delete lpBits1;
	delete lpBits2;
	delete lpBits3;
}
void CMFCApplication1Dlg::Ondraw(void){
	HBITMAP hb;
	//hb = (HBITMAP)bitmap.GetSafeHandle();
	//MY_PICTURE.ModifyStyle(0xF, SS_BITMAP);
	//MY_PICTURE.SetBitmap(hb);
	CDC* pdc = MY_PICTURE.GetDC();
	CDC dmeu;
	dmeu.CreateCompatibleDC(pdc);
	CRect rc;
	MY_PICTURE.GetClientRect(&rc);
	hb = (HBITMAP)dmeu.SelectObject(bitmap);
	pdc->BitBlt(0, 0, rc.Width(), rc.Height(), &dmeu, 0, 0, SRCCOPY);
	dmeu.SelectObject(hb);
	dmeu.DeleteDC();
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)//定时器消息处理，Settimer是设置定时器的，Ontimer是响应Settimer消息的。当Settimer设置的时间到了，就会自动调动Ontimer()函数。
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	Sleep(100);
	m = nIndex;
	nIndex++;//顺序显示
	if (nIndex == MAX_COUNT)
		nIndex = 0;//处理溢出现象
	n = nIndex;
	getCBitmapFade();//图片淡入淡出函数
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication1Dlg::OnBnClickedjiequ()//截取视频图片
{
	// TODO:  在此添加控件通知处理程序代码
	CvCapture* capture = cvCaptureFromAVI("美丽的神话.avi");
	IplImage* img = 0;
	/*IplImage* img2 = 0 ;
	IplImage* img3 = 0;*/
	int i = 0;
	char image_name[7384];
	//cvNamedWindow("vivi");
	//读取和显示  
	for (i = 0;;i=i+1)
	{
		img = cvQueryFrame(capture); //获取一帧图片  
		if (img == NULL)
			break;
		//cvShowImage("vivi", img); //将其显示  
			sprintf(image_name, "%s%d%s", "image", i, ".bmp");//保存的图片名  
			cvSaveImage(image_name, img);   //保存一帧图片 
		//*********************
			//img2 = cvQueryFrame(capture); //获取一帧图片  
			//if (img2 == NULL)
			//	break;
			////cvShowImage("vivi", img); //将其显示  
			//sprintf(image_name, "%s%d%s", "image", i+1, ".bmp");//保存的图片名  
			//cvSaveImage(image_name, img2);   //保存一帧图片 
			////*********************
			//img3 = cvQueryFrame(capture); //获取一帧图片  
			//if (img3 == NULL)
			//	break;
			////cvShowImage("vivi", img); //将其显示  
			//sprintf(image_name, "%s%d%s", "image", i + 1, ".bmp");//保存的图片名  
			//cvSaveImage(image_name, img3);   //保存一帧图片 
	}
	cvReleaseCapture(&capture);
}
void CMFCApplication1Dlg::OnBnClickedQuery()//查询内容，比如RGB三位通道上为红蓝绿的图片，并且输出图片名到red.txt,blue.txt,green.txt.
{
	// TODO:  在此添加控件通知处理程序代码
	int i = 0;
	int x = 0;
	char image_name[7383];
	char image_name1[7383];
	char image_name2[7383];
	char image_name3[7383];
	std::ofstream f1("C:\\huangxingxing\\multi-core-pragrammming\\MFCApplication1\\MFCApplication1\\red.txt", std::ios::app);
	std::ofstream f2("C:\\huangxingxing\\multi-core-pragrammming\\MFCApplication1\\MFCApplication1\\green.txt", std::ios::app);
	std::ofstream f3("C:\\huangxingxing\\multi-core-pragrammming\\MFCApplication1\\MFCApplication1\\blue.txt", std::ios::app);
	CvScalar sc;
	for (; i < 7383;){
		sprintf(image_name, "%s%d%s", "image", i, ".bmp");
		IplImage* resimage = cvLoadImage(image_name, CV_LOAD_IMAGE_COLOR);
		/*CBitmap* cbmp = Iplimage2Bitmap(resimage);
		cbmp->GetBitmap(&b);*/
		for (int y = 0; y < resimage->height; y++)//b.bmHeight代表有多少行
		{
			#pragma omp parallel for num_threads(12) private(x)
			for (int x = 0; x < resimage->width; x = x + 12)// b.bmWidth代表有一行像素点
			{
				//.........................
				sc = cvGet2D(resimage, y, x);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 1);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 2);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 3);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 4);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 5);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 6);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 7);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 8);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 9);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 10);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
				//.........................
				sc = cvGet2D(resimage, y, x + 11);//找到像素点，取出像素点的值
				if (sc.val[0] == 255){
					sprintf(image_name1, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[1] == 255){
					sprintf(image_name2, "%s%d%s", "image", i, ".bmp");

				}
				if (sc.val[2] == 255){
					sprintf(image_name3, "%s%d%s", "image", i, ".bmp");

				}
			}
		}
		i = i + 1;
	}
	f1 << "  " << image_name1;
	f2 << "  " << image_name2;
	f3 << "  " << image_name3;
	f1.close();
	f2.close();
	f3.close();
}
