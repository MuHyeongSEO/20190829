
// ImageProc_20190829Doc.cpp: CImageProc20190829Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20190829.h"
#endif

#include "ImageProc_20190829Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProc20190829Doc

IMPLEMENT_DYNCREATE(CImageProc20190829Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc20190829Doc, CDocument)
END_MESSAGE_MAP()


// CImageProc20190829Doc 생성/소멸

CImageProc20190829Doc::CImageProc20190829Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	InputIMG = NULL;
	InputIMG2 = NULL;
	ResultIMG = NULL;
}

CImageProc20190829Doc::~CImageProc20190829Doc()
{
	int i;
	if (InputIMG != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(InputIMG[i]);
		free(InputIMG);
	}
	if (ResultIMG != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(ResultIMG[i]);
		free(ResultIMG);
	}
	if (InputIMG2 != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(InputIMG2[i]);
		free(InputIMG2);
	}
}

BOOL CImageProc20190829Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProc20190829Doc serialization

void CImageProc20190829Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		LoadImageFile(ar);
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProc20190829Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CImageProc20190829Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc20190829Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProc20190829Doc 진단

#ifdef _DEBUG
void CImageProc20190829Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc20190829Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProc20190829Doc 명령


void CImageProc20190829Doc::LoadImageFile(CArchive& ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 || strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{ 
			AfxMessageBox("256*256크기의 raw파일만 읽을 수 있습니다.");
				return;
		}
		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}

	InputIMG = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	ResultIMG = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	
	for(int i = 0; i < ImageHeight; i++)
	{
		InputIMG[i] = (unsigned char*)malloc(ImageWidth * depth);
		ResultIMG[i] = (unsigned char*)malloc(ImageWidth * depth);
	}
	// TODO: 여기에 구현 코드 추가.
	// 영상데이터 읽기
	for (int i = 0; i < ImageHeight; i++)
	{	
		ar.Read(InputIMG[i], ImageWidth * depth);
	}

}


void CImageProc20190829Doc::LoadSecondImageFile(CArchive& ar)
{
	int maxValue;
	int temp_w, temp_h, temp_depth;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 || strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &temp_w, &temp_h);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) temp_depth = 1;
		else temp_depth = 3;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256*256크기의 raw파일만 읽을 수 있습니다.");
			return;
		}
		temp_w = 256;
		temp_h = 256;
		temp_depth = 1;
	}

	if (ImageWidth != temp_w || ImageHeight != temp_h || depth != temp_depth)
	{
		AfxMessageBox("두번째 파일의 width,height,depth가 다르면 읽을수 없습니다.");
		return;
	}
		
	//메모리 할당	
	InputIMG2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));


	for (int i = 0; i < ImageHeight; i++)
	{
		InputIMG2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}
	// 영상데이터 읽기
	for (int i = 0; i < ImageHeight; i++)
	{
		ar.Read(InputIMG2[i], ImageWidth * depth);
	}
}
