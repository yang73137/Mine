
// MineDoc.cpp : CMineDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Mine.h"
#endif

#include "MineDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMineDoc

IMPLEMENT_DYNCREATE(CMineDoc, CDocument)

BEGIN_MESSAGE_MAP(CMineDoc, CDocument)
END_MESSAGE_MAP()


// CMineDoc 构造/析构

CMineDoc::CMineDoc()
{
	// TODO: 在此添加一次性构造代码
	this->m_increase = 23;
	this->m_max = 12;
	this->m_index = 2;

	this->m_numX = this->m_numY = 9;

	this->m_ticks = 0;
	this->m_maxTicks = 999;
	this->m_timerId = 9999;
	this->m_leftMines = 10;

	for (UINT y = 0; y < this->m_numY; y++)
	{
		for (UINT x = 0; x < this->m_numX; x++)
		{	
			this->m_mines[x][y].m_width = 16;
			this->m_mines[x][y].m_height = 16;
			this->m_mines[x][y].m_status = MineStatus::Normal;
		}
	}
}

CMineDoc::~CMineDoc()
{
}

BOOL CMineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMineDoc 序列化

void CMineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMineDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMineDoc 诊断

#ifdef _DEBUG
void CMineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMineDoc 命令
void CMineDoc::DrawTimer(CDC* pDC)
{
	CBitmap bm;
	bm.LoadBitmapW(IDB_TIMER);

	BITMAP b;
	bm.GetBitmap(&b);

	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(bm);
	pDC->BitBlt(0, 0, b.bmWidth, this->m_increase, &memDC, 0, this->m_increase * this->m_index, SRCCOPY);
}