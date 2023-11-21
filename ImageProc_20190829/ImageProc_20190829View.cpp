
// ImageProc_20190829View.cpp: CImageProc20190829View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20190829.h"
#endif

#include "ImageProc_20190829Doc.h"
#include "ImageProc_20190829View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProc20190829View

IMPLEMENT_DYNCREATE(CImageProc20190829View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20190829View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_PIXEL_ADD, &CImageProc20190829View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImageProc20190829View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProc20190829View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProc20190829View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProc20190829View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_STRETCHING, &CImageProc20190829View::OnPixelStretching)
	ON_COMMAND(ID_PIXEL_BIRNARIZATION, &CImageProc20190829View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProc20190829View::OnPixelBinarization)
	ON_COMMAND(ID_TWO_IMAGE_ADD, &CImageProc20190829View::OnTwoImageAdd)
	ON_COMMAND(ID_TWO_IMAGE_SUB, &CImageProc20190829View::OnTwoImageSub)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProc20190829View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SMOOTHING, &CImageProc20190829View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_EMBOSSING, &CImageProc20190829View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CImageProc20190829View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CImageProc20190829View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProc20190829View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProc20190829View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MID_FILTERING, &CImageProc20190829View::OnRegionMidFiltering)
END_MESSAGE_MAP()

// CImageProc20190829View 생성/소멸

CImageProc20190829View::CImageProc20190829View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProc20190829View::~CImageProc20190829View()
{
}

BOOL CImageProc20190829View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProc20190829View 그리기

void CImageProc20190829View::OnDraw(CDC*pDC)
{
	CImageProc20190829Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//pDC->TextOutA(100, 100, "화면에 출력되는 메세지입니다.");
	//pDC->Rectangle(10, 20, 100, 300);
	int x, y;
	if (pDoc->InputIMG != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputIMG[y][x], pDoc->InputIMG[y][x], pDoc->InputIMG[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputIMG[y][3 * x + 0], pDoc->InputIMG[y][3 * x + 1], pDoc->InputIMG[y][3 * x + 2]));
		}

		/*for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; pDoc->ImageWidth; x++)
				pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultIMG[y][x], pDoc->ResultIMG[y][x], pDoc->ResultIMG[y][x]));

		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; pDoc->ImageWidth; x++)
				pDC->SetPixel(pDoc->ImageWidth + 20 * 2 + x, y, RGB(pDoc->InputIMG2[y][x], pDoc->InputIMG2[y][x], pDoc->InputIMG2[y][x]));*/
	}
	if (pDoc->ResultIMG != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultIMG[y][x], pDoc->ResultIMG[y][x], pDoc->ResultIMG[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultIMG[y][3 * x + 0], pDoc->ResultIMG[y][3 * x + 1], pDoc->ResultIMG[y][3 * x + 2]));
		}
	}
	if (pDoc->InputIMG2 != NULL)
	{
		if (pDoc->depth == 1) 
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth * 2 + 40 + x, y, RGB(pDoc->InputIMG2[y][x], pDoc->InputIMG2[y][x], pDoc->InputIMG2[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth * 2 + 40 + x, y, RGB(pDoc->InputIMG2[y][3 * x + 0], pDoc->InputIMG2[y][3 * x + 1], pDoc->InputIMG2[y][3 * x + 2]));
		}
	}
}

void CImageProc20190829View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20190829View 인쇄

BOOL CImageProc20190829View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProc20190829View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProc20190829View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProc20190829View 진단

#ifdef _DEBUG
void CImageProc20190829View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20190829View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20190829Doc* CImageProc20190829View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20190829Doc)));
	return (CImageProc20190829Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc20190829View 메시지 처리기


void CImageProc20190829View::OnPixelAdd()
{
	CImageProc20190829Doc* pDoc = GetDocument();
	if (pDoc->InputIMG == NULL)
		return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputIMG[y][x] + 100;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][x] = value;
			}
			else
			{
				value = pDoc->InputIMG[y][3 * x + 0] + 100;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 0] = value;
				//RED

				value = pDoc->InputIMG[y][3 * x + 1] + 100;
				
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 1] = value;
				//GREEN

				value = pDoc->InputIMG[y][3 * x + 2] + 100;
				
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 2] = value;
			}
		}

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnPixelSub()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	if(pDoc->InputIMG == NULL)
		return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputIMG[y][x] - 100;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][x] = value;
			}
			else
			{
				value = pDoc->InputIMG[y][3 * x + 0] - 100;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 0] = value;
				//RED

				value = pDoc->InputIMG[y][3 * x + 1] - 100;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 1] = value;
				//GREEN

				value = pDoc->InputIMG[y][3 * x + 2] - 100;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 2] = value;
			}
		}

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnPixelMul()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	if (pDoc->InputIMG == NULL)
		return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputIMG[y][x] * 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][x] = value;
			}
			else
			{
				value = pDoc->InputIMG[y][3 * x + 0] * 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 0] = value;
				//RED

				value = pDoc->InputIMG[y][3 * x + 1] * 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 1] = value;
				//GREEN

				value = pDoc->InputIMG[y][3 * x + 2] * 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 2] = value;
			}
		}

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnPixelDiv()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	if (pDoc->InputIMG == NULL)
		return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputIMG[y][x] / 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][x] = value;
			}
			else
			{
				value = pDoc->InputIMG[y][3 * x + 0] / 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 0] = value;
				//RED

				value = pDoc->InputIMG[y][3 * x + 1] / 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 1] = value;
				//GREEN

				value = pDoc->InputIMG[y][3 * x + 2] / 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultIMG[y][3 * x + 2] = value;
			}
		}

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnPixelHistoEq()
{
	CImageProc20190829Doc* pDoc = GetDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i, x, y, value;
	int acc_hist;
	int N = 256 * 256;
	int hist[256], sum[256];
	
	for (i = 0; i < 256; i++)
	{
		hist[i] = 0;
	}
	//히스토그램 구하기
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) 
		{
			value = pDoc->InputIMG[y][x];
			hist[value]++;
		}
	//누적 분포
	acc_hist = 0;
	for (i = 0; i < 256; i++)
	{
		acc_hist += hist[i];
		sum[i] = acc_hist;

	}
	//픽셀 밝기 변화
	for(y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			value = pDoc->InputIMG[y][x];
			pDoc->ResultIMG[y][x] = (float)sum[value] / N * 255;
		}
	Invalidate();
}


void CImageProc20190829View::OnPixelStretching()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}



void CImageProc20190829View::OnPixelBinarization()
{

	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, value;
	int threshold = 100;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) 
		{
			if (pDoc->InputIMG[y][x] > threshold) pDoc->ResultIMG[y][x] = 255;
			else pDoc->ResultIMG[y][x] = 0;
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::LoadTwoImage()
{
	CImageProc20190829Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		CFile file;
		file.Open(dlg.GetPathName(), CFile::modeRead); //파일열기
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		//file.Read(pDoc->InputIMG2, 256 * 256);
		file.Close();

	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProc20190829View::OnTwoImageAdd()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	LoadTwoImage();
	int x, y, value;

	for(y = 0; y < pDoc-> ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			value = 0.5*pDoc->InputIMG[y][x] + 0.5*pDoc->InputIMG2[y][x];
			if (value > 255)value = 256;
			else if (value < 0) value = 0;
			pDoc->ResultIMG[y][x] = value;
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnTwoImageSub()
{

	CImageProc20190829Doc* pDoc = GetDocument();

	LoadTwoImage();
	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			value = pDoc->InputIMG[y][x] - pDoc->InputIMG2[y][x];
			if (value > 255)value = 255;
			else if (value < 0) value = 0;
			if (value > 64) value = 255;
			else value = 0;
			pDoc->ResultIMG[y][x] = value;
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnRegionSharpening()
{
	CImageProc20190829Doc* pDoc = GetDocument();
	float kernel[3][3] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0} };
	
	convolve(pDoc->InputIMG, pDoc->ResultIMG, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);
	
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3] , int bias, int depth)
{
	int x, y, i, j, sum, rsum, gsum, bsum;
	for (y = 1; y < rows-1; y++)
		for (x = 1; x < cols-1; x++)
		{
			if (depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += (inimg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255)
					sum = 255;
				else if (sum < 0)
					sum = 0;
				outimg[y][x] = sum;
			}
			else
			{
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (inimg[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i]);
						gsum += (inimg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inimg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}
				rsum += bias;
				gsum += bias;
				bsum += bias;
				//red
				if (rsum > 255)
					rsum = 255;
				else if (rsum < 0)
					rsum = 0;
				//green
				if (gsum > 255)
					gsum = 255;
				else if (gsum < 0)
					gsum = 0;
				//blue
				if (bsum > 255)
					bsum = 255;
				else if (bsum < 0)
					bsum = 0;
				outimg[y][3 * x + 0] = rsum;
				outimg[y][3 * x + 1] = gsum;
				outimg[y][3 * x + 2] = bsum;
			}
		}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProc20190829View::OnRegionSmoothing()
{
	CImageProc20190829Doc* pDoc = GetDocument();
	float kernel[3][3] = { {1 / 9.0f, 1 / 9.0f, 1 / 9.0f}, {1 / 9.0f, 1 / 9.0f, 1 / 9.0f}, {1 / 9.0f, 1 / 9.0f, 1 / 9.0f} };

	convolve(pDoc->InputIMG, pDoc->ResultIMG, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnRegionEmbossing()
{
	CImageProc20190829Doc* pDoc = GetDocument();
	float kernel[3][3] = { {1, 0, 0}, {0,0,0}, {0, 0, -1} };

	convolve(pDoc->InputIMG, pDoc->ResultIMG, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 128, pDoc->depth);

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CImageProc20190829View::OnRegionPrewitt()
{
	int x, y, i, value, rvalue, gvalue, bvalue;
	CImageProc20190829Doc* pDoc = GetDocument();
	float kernel_h[3][3] = { {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} };
	float kernel_v[3][3] = { {-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1} };

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc -> depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->InputIMG, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->InputIMG, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y<pDoc-> ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)
					value = 255;
				else if (value < 0)
					value = 0;
				pDoc->ResultIMG[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)
					value = 255;
				else if (value < 0)
					value = 0;
				pDoc->ResultIMG[y][3 * x + 0] = value;
				pDoc->ResultIMG[y][3 * x + 1] = value;
				pDoc->ResultIMG[y][3 * x + 2] = value;
			}
		}
		
	//메모리 삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);

	}
	free(Er);
	free(Ec);

	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnRegionRoberts()
{
	{
		int x, y, i, value, rvalue, gvalue, bvalue;
		CImageProc20190829Doc* pDoc = GetDocument();
		float kernel_h[3][3] = { {1, 0, 0}, {0, -1, 0}, {0, 0, 0} };
		float kernel_v[3][3] = { {0, 1, 0}, {-1, 0, 0}, {0, 0, 0} };

		unsigned char** Er, ** Ec;
		Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
		Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
		for (i = 0; i < pDoc->ImageHeight; i++)
		{
			Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
			Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		}

		convolve(pDoc->InputIMG, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
		convolve(pDoc->InputIMG, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
					if (value > 255)
						value = 255;
					else if (value < 0)
						value = 0;
					pDoc->ResultIMG[y][x] = value;
				}
				else
				{
					rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
					gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
					bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
					value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
					if (value > 255)
						value = 255;
					else if (value < 0)
						value = 0;
					pDoc->ResultIMG[y][3 * x + 0] = value;
					pDoc->ResultIMG[y][3 * x + 1] = value;
					pDoc->ResultIMG[y][3 * x + 2] = value;
				}
			}

		//메모리 삭제
		for (i = 0; i < pDoc->ImageHeight; i++)
		{
			free(Er[i]);
			free(Ec[i]);

		}
		free(Er);
		free(Ec);

		Invalidate();
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnRegionSobel()
{
	{
		int x, y, i, value, rvalue, gvalue, bvalue;
		CImageProc20190829Doc* pDoc = GetDocument();
		float kernel_h[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
		float kernel_v[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

		unsigned char** Er, ** Ec;
		Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
		Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
		for (i = 0; i < pDoc->ImageHeight; i++)
		{
			Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
			Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		}

		convolve(pDoc->InputIMG, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
		convolve(pDoc->InputIMG, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
					if (value > 255)
						value = 255;
					else if (value < 0)
						value = 0;
					pDoc->ResultIMG[y][x] = value;
				}
				else
				{
					rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
					gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
					bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
					value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
					if (value > 255)
						value = 255;
					else if (value < 0)
						value = 0;
					pDoc->ResultIMG[y][3 * x + 0] = value;
					pDoc->ResultIMG[y][3 * x + 1] = value;
					pDoc->ResultIMG[y][3 * x + 2] = value;
				}
			}

		//메모리 삭제
		for (i = 0; i < pDoc->ImageHeight; i++)
		{
			free(Er[i]);
			free(Ec[i]);

		}
		free(Er);
		free(Ec);

		Invalidate();
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnRegionAverageFiltering()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, i, j, xpos, ypos, sum, pixelcount, rsum, gsum, bsum;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			sum = 0;
			rsum = 0;
			gsum = 0;
			bsum = 0;
			pixelcount = 0;
			for (j = -2; j <= 2; j++)
				for(i = -2; i <= 2; i++)
				{
					xpos = x + i;
					ypos = y + j;
					if (xpos >= 0 && xpos <= pDoc->ImageWidth - 1 && ypos >= 0 && ypos <= pDoc->ImageHeight - 1)
					{
						if(pDoc->depth ==1)
							sum += pDoc->InputIMG[y + j][x + i];
						else
						{
							rsum += pDoc->InputIMG[y + j][3 * (x + i) + 0];
							gsum += pDoc->InputIMG[y + j][3 * (x + i) + 1];
							bsum += pDoc->InputIMG[y + j][3 * (x + i) + 2];
						}
						pixelcount++;
					}
				}
			if (pDoc->depth == 1)
				pDoc-> ResultIMG[y][x] = sum / pixelcount;
			else
			{
				pDoc->ResultIMG[y][3 * x + 0] = rsum / pixelcount;
				pDoc->ResultIMG[y][3 * x + 1] = gsum / pixelcount;
				pDoc->ResultIMG[y][3 * x + 2] = bsum / pixelcount;
			}
		}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Invalidate();
}


void CImageProc20190829View::OnRegionMidFiltering()
{
	CImageProc20190829Doc* pDoc = GetDocument();
	int x, y, i, j, temp;
	int n[9];
	for (y = 0; y < pDoc->ImageHeight - 1; y++)
		for (x = 0; x < pDoc->ImageWidth - 1; x++)
		{
			n[0] = pDoc->InputIMG[y - 1][x - 1];
			n[1] = pDoc->InputIMG[y - 1][x - 0];
			n[2] = pDoc->InputIMG[y - 1][x + 1];

			n[3] = pDoc->InputIMG[y - 1][x - 1];
			n[4] = pDoc->InputIMG[y - 0][x - 0];
			n[5] = pDoc->InputIMG[y - 0][x + 1];

			n[6] = pDoc->InputIMG[y + 1][x - 1];
			n[7] = pDoc->InputIMG[y + 0][x - 0];
			n[8] = pDoc->InputIMG[y + 0][x + 1];

			//버블 소팅(오름차순)
			for (i = 8; i > 0; i--)
				for (j = 0; j < i; j++)
				{
					if (n[j] > n[j + 1])
					{
						temp = n[j + i];
						n[j + 1] = n[j];
						n[j] = temp;
					}
				}
			pDoc->ResultIMG[y][x] = n[4];
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
