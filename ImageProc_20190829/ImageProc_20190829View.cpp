
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
#include "CAngleInputDialog.h"

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
	ON_COMMAND(ID_MOPOLOGY_GRAY, &CImageProc20190829View::OnMopologyGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImageProc20190829View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CImageProc20190829View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CImageProc20190829View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CImageProc20190829View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImageProc20190829View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20190829View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEAR_INTERPOLATION, &CImageProc20190829View::OnGeometryZoominBilinearInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProc20190829View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETY_ZOOMOUT_MEANSUB, &CImageProc20190829View::OnGeometyZoomoutMeansub)
	ON_COMMAND(ID_GEOMETRY_AVG_SAMPLING, &CImageProc20190829View::OnGeometryAvgSampling)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20190829View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CImageProc20190829View::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CImageProc20190829View::OnGeometryFlip)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CImageProc20190829View::OnGeometryWarping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//ON_COMMAND(ID_AVI_VIEW, &CImageProc20190829View::OnAviView)
END_MESSAGE_MAP()

// CImageProc20190829View 생성/소멸

CImageProc20190829View::CImageProc20190829View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	bAviMode = false;
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


void CImageProc20190829View::OnMopologyGray()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y;
	int gray;

	if (pDoc->depth == 1) return;

	for (y = 1; y < pDoc->ImageHeight; y++)
		for (x = 1; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->InputIMG[y][3 * x + 0] + pDoc->InputIMG[y][3 * x + 1] + pDoc->InputIMG[y][3 * x + 2]) / 3;
			pDoc->InputIMG[y][3 * x + 0] = gray;
			pDoc->InputIMG[y][3 * x + 1] = gray;
			pDoc->InputIMG[y][3 * x + 2] = gray;
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnMopologyBinarization()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y;
	int gray, threshold = 100;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->InputIMG[y][x] > threshold) pDoc->InputIMG[y][x] = 255;
				else pDoc->InputIMG[y][x] = 0;
			}
			else
			{
				if ((pDoc->InputIMG[y][3 * x + 0] + pDoc->InputIMG[y][3 * x + 1] + pDoc->InputIMG[y][3 * x + 2]) / 3 > threshold)
				{
					pDoc->InputIMG[y][3 * x + 0] = 255;
					pDoc->InputIMG[y][3 * x + 1] = 255;
					pDoc->InputIMG[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InputIMG[y][3 * x + 0] = 0;
					pDoc->InputIMG[y][3 * x + 1] = 0;
					pDoc->InputIMG[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnMopologyErosion()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, i, j;
	int min = 255, rmin, gmin, bmin;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			min = 255; rmin = 255; gmin = 255; bmin = 255;
			for (j = -1; j <= 1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->InputIMG[y + j][x + i] < min)
							min = pDoc->InputIMG[y + j][x + i];
					}
					else
					{
						if (pDoc->InputIMG[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->InputIMG[y + j][3 * (x + i) + 0];

						if (pDoc->InputIMG[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InputIMG[y + j][3 * (x + i) + 1];

						if (pDoc->InputIMG[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InputIMG[y + j][3 * (x + i) + 2];
					}
				}
			if (pDoc->depth == 1)
				pDoc->ResultIMG[y][x] = min;
			else
			{
				pDoc->ResultIMG[y][3 * x + 0] = rmin;
				pDoc->ResultIMG[y][3 * x + 1] = gmin;
				pDoc->ResultIMG[y][3 * x + 2] = bmin;
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnMopologyDilation()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, i, j;
	int max, rmax, gmax, bmax;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			max = 0; rmax = 0; gmax = 0; bmax = 0;
			for (j = -1; j <= 1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->InputIMG[y + j][x + i] > max)
							max = pDoc->InputIMG[y + j][x + i];
					}
					else
					{
						if (pDoc->InputIMG[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InputIMG[y + j][3 * (x + i) + 0];

						if (pDoc->InputIMG[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InputIMG[y + j][3 * (x + i) + 1];

						if (pDoc->InputIMG[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InputIMG[y + j][3 * (x + i) + 2];
					}
				}
			if (pDoc->depth == 1)
				pDoc->ResultIMG[y][x] = max;
			else
			{
				pDoc->ResultIMG[y][3 * x + 0] = rmax;
				pDoc->ResultIMG[y][3 * x + 1] = gmax;
				pDoc->ResultIMG[y][3 * x + 2] = bmax;
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


	
void CImageProc20190829View::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnGeometryZoominPixelCopy()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, i;
	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultIMG != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultIMG[i]);
		free(pDoc->gResultIMG);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;

	// 메모리 할당
	pDoc->gResultIMG = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultIMG[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	/* 전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
				pDoc->gResultIMG[y * yscale][x * xscale] = pDoc->InputIMG[y][x];
		}
		*/

		// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1)
				pDoc->gResultIMG[y][x] = pDoc->InputIMG[y / yscale][x / xscale];
			else {
				pDoc->gResultIMG[y][3 * x + 0] = pDoc->InputIMG[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultIMG[y][3 * x + 1] = pDoc->InputIMG[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultIMG[y][3 * x + 2] = pDoc->InputIMG[y / yscale][3 * (x / xscale) + 2];
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnGeometryZoominBilinearInterpolation()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, i;

	float xscale = 2.1;
	float yscale = 1.5;

	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;

	int E, F;

	if (pDoc->gResultIMG != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultIMG[i]);
		free(pDoc->gResultIMG);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) * xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) * yscale;

	// 메모리 할당
	pDoc->gResultIMG = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultIMG[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++) {
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x; // 소수점만 남기기
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ax + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1) {

				E = (1 - alpha) * pDoc->InputIMG[Ay][Ax] + alpha * pDoc->InputIMG[By][Bx];
				F = (1 - alpha) * pDoc->InputIMG[Cy][Cx] + alpha * pDoc->InputIMG[Dy][Dx];

				pDoc->gResultIMG[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->InputIMG[Ay][3 * Ax + 0] + alpha * pDoc->InputIMG[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->InputIMG[Cy][3 * Cx + 0] + alpha * pDoc->InputIMG[Dy][3 * Dx + 0];
				pDoc->gResultIMG[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputIMG[Ay][3 * Ax + 1] + alpha * pDoc->InputIMG[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->InputIMG[Cy][3 * Cx + 1] + alpha * pDoc->InputIMG[Dy][3 * Dx + 1];
				pDoc->gResultIMG[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputIMG[Ay][3 * Ax + 2] + alpha * pDoc->InputIMG[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->InputIMG[Cy][3 * Cx + 2] + alpha * pDoc->InputIMG[Dy][3 * Dx + 2];
				pDoc->gResultIMG[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnGeometryZoomoutSubsampling()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, i;

	int xscale = 3; // 1/3로 축소
	int yscale = 2; // 1/2로 축소

	if (pDoc->gResultIMG != NULL) // 메모리가 할당되어 있으면 전부 삭제
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultIMG[i]);
		free(pDoc->gResultIMG);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	// 메모리 할당
	pDoc->gResultIMG = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultIMG[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				pDoc->gResultIMG[y][x] = pDoc->InputIMG[y * yscale][x * xscale];
			}
			else
			{
				pDoc->gResultIMG[y][3 * x + 0] = pDoc->InputIMG[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultIMG[y][3 * x + 1] = pDoc->InputIMG[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultIMG[y][3 * x + 2] = pDoc->InputIMG[y * yscale][3 * (x * xscale) + 2];
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnGeometyZoomoutMeansub()
{
	OnRegionSmoothing();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnGeometryAvgSampling()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y, i, j;
	int sum, rsum, gsum, bsum;

	int xscale = 3; // 1/3로 축소
	int yscale = 2; // 1/2로 축소
	int src_x, src_y;

	if (pDoc->gResultIMG != NULL) // 메모리가 할당되어 있으면 전부 삭제
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultIMG[i]);
		free(pDoc->gResultIMG);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	// 메모리 할당
	pDoc->gResultIMG = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultIMG[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	// 전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y += yscale)
		for (x = 0; x < pDoc->ImageWidth; x += xscale) {
			sum = 0, rsum = 0, gsum = 0, bsum = 0;
			for (j = 0; j < yscale; j++)
				for (i = 0; i < xscale; i++) {
					src_x = x + i;
					src_y = y + j;
					if (src_x > pDoc->ImageWidth - 1) src_x > pDoc->ImageWidth - 1;
					if (src_y > pDoc->ImageHeight - 1) src_y > pDoc->ImageHeight - 1;

					if (pDoc->depth == 1)
						sum += pDoc->InputIMG[src_y][src_x];
					else
					{
						rsum += pDoc->InputIMG[src_y][3 * src_x + 0];
						gsum += pDoc->InputIMG[src_y][3 * src_x + 1];
						bsum += pDoc->InputIMG[src_y][3 * src_x + 2];
					}
				}
			if (pDoc->depth == 1)
				pDoc->gResultIMG[y / yscale][x / xscale] = sum / (xscale * yscale);
			else
			{
				pDoc->gResultIMG[y / yscale][3 * (x / xscale) + 0] = rsum / (xscale * yscale);
				pDoc->gResultIMG[y / yscale][3 * (x / xscale) + 1] = gsum / (xscale * yscale);
				pDoc->gResultIMG[y / yscale][3 * (x / xscale) + 2] = bsum / (xscale * yscale);
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


#define PI 3.1415926521
void CImageProc20190829View::OnGeometryRotation()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	CAngleInputDialog dlg;

	int x, y, i, j;
	int angle = 30; // 단위 : degree
	float radian;
	int Cx, Cy, Oy;
	int x_source, y_source, xdiff, ydiff;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;

	if (pDoc->gResultIMG != NULL) // 메모리가 할당되어 있으면 전부 삭제
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultIMG[i]);
		free(pDoc->gResultIMG);
	}

	radian = 2 * PI / 360 * angle;
	pDoc->gImageWidth = pDoc->ImageHeight * fabs(cos(PI / 2 - radian)) + pDoc->ImageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageHeight * fabs(cos(PI / 2 - radian));

	// 메모리 할당
	pDoc->gResultIMG = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultIMG[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	// 중심점
	Cx = pDoc->ImageWidth / 2; Cy = pDoc->ImageHeight / 2;

	// y의 마지막 좌표
	Oy = pDoc->ImageHeight - 1;
	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = (Oy - y - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Oy - ((Oy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			//y_source = Oy - y_source;
			if (pDoc->depth == 1)
			{
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1)
					pDoc->gResultIMG[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultIMG[y + ydiff][x + xdiff] = pDoc->InputIMG[y_source][x_source];
			}
			else
			{
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1)
				{
					pDoc->gResultIMG[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultIMG[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultIMG[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultIMG[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputIMG[y_source][3 * (x_source)+0];
					pDoc->gResultIMG[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputIMG[y_source][3 * (x_source)+1];
					pDoc->gResultIMG[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputIMG[y_source][3 * (x_source)+2];
				}
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnGeometryMirror()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->ResultIMG[y][x] = pDoc->InputIMG[y][pDoc->ImageWidth - 1 - x];
			else
			{
				pDoc->ResultIMG[y][3 * x + 0] = pDoc->InputIMG[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->ResultIMG[y][3 * x + 1] = pDoc->InputIMG[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->ResultIMG[y][3 * x + 2] = pDoc->InputIMG[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::OnGeometryFlip()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->ResultIMG[y][x] = pDoc->InputIMG[pDoc->ImageHeight - 1 - y][x];
			else
			{
				pDoc->ResultIMG[y][3 * x + 0] = pDoc->InputIMG[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->ResultIMG[y][3 * x + 1] = pDoc->InputIMG[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->ResultIMG[y][3 * x + 2] = pDoc->InputIMG[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

typedef struct // typedef : 새로운 자료형 정의
{
	int Px;
	int Py;
	int Qx;
	int Qy;
}control_line;

control_line mctrl_source = { 100, 100, 150, 150 };
control_line mctrl_dest = { 100, 100, 200, 200 };


void CImageProc20190829View::OnGeometryWarping()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	control_line source_lines[5] = { { 100, 100, 150, 150 },
		{ 0, 0, pDoc->ImageWidth - 1, 0 }, { pDoc->ImageWidth - 1, 0, pDoc->ImageWidth - 1, pDoc->ImageHeight - 1 },
		{ pDoc->ImageWidth - 1, pDoc->ImageHeight - 1, 0, pDoc->ImageHeight - 1 }, { 0, pDoc->ImageHeight - 1, 0, 0 } };

	control_line dest_lines[5] = { { 100, 100, 200, 200 },
		{ 0, 0, pDoc->ImageWidth - 1, 0 }, { pDoc->ImageWidth - 1, 0, pDoc->ImageWidth - 1, pDoc->ImageHeight - 1 },
		{ pDoc->ImageWidth - 1, pDoc->ImageHeight - 1, 0, pDoc->ImageHeight - 1 }, { 0, pDoc->ImageHeight - 1, 0, 0 } };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;
	int x, y;

	double u;
	double h;
	double d;
	double tx, ty;
	double xp, yp;

	double weight;
	double totalweight;
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, x2, y1, y2;
	int src_x1, src_x2, src_y1, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;
	int line;
	int source_x, source_y;
	int last_row, last_col;

	last_row = pDoc->ImageHeight - 1;
	last_col = pDoc->ImageWidth - 1;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalweight = 0.0;

			// 각 제어선의 영향을 계산
			for (line = 0; line < num_lines; line++) {
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0) d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1) d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else d = fabs(h); // fabs : 절댓값

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalweight += weight;
			}
			source_x = x + (tx / totalweight);
			source_y = y + (ty / totalweight);

			if (source_x < 0)		 source_x = 0;
			if (source_x > last_col) source_x = last_col;
			if (source_y < 0)		 source_y = 0;
			if (source_y > last_row) source_y = last_row;

			if (pDoc->depth == 1)
				pDoc->ResultIMG[y][x] = pDoc->InputIMG[source_y][source_x];
			else
			{
				pDoc->ResultIMG[y][3 * x + 0] = pDoc->InputIMG[source_y][3 * source_x + 0];
				pDoc->ResultIMG[y][3 * x + 1] = pDoc->InputIMG[source_y][3 * source_x + 1];
				pDoc->ResultIMG[y][3 * x + 2] = pDoc->InputIMG[source_y][3 * source_x + 2];
			}
		}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


CPoint mpos_st, mpos_end;
void CImageProc20190829View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CImageProc20190829View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&rpen);

	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);

	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax < Bx) mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else mctrl_source.Px = Ax + (Ax - Bx) / 2;

	if (Ay < By) mctrl_source.Py = Ay - (By - Ay) / 2;
	else mctrl_source.Py = Ay + (Ay - By) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageProc20190829View::OnAviView()
{
	CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI파일(*.avi) | .avi | .AVI | 모든 파일 | *.*|");

	if (dlg.DoModal() == IDOK)
	{
		AVIFileName = dlg.GetPathName();
		bAviMode = true;
		Invalidate();
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20190829View::LoadAviFile(CDC* pDC)
{/*
	// TODO: 여기에 구현 코드 추가.
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AVIFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++) {
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame < 100; frame++) // 원래는 frame < si.dwLength
			{
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih) continue;

				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);
				//
				for(y = 0; y < fi.dwHeight; y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwHeight - 1 - y,
							RGB(image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]));
					}
					//
				::SetDIBitsToDevice(pDC->GetSafeHdc(),
					0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth,
					image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(30);
			}
		}
	}*/
}

void CImageProc20190829View::CopyResultToInput()
{
	CImageProc20190829Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			pDoc->InputIMG[y][x] = pDoc->ResultIMG[y][x];
		}
	// TODO: 여기에 구현 코드 추가.
}
