
// ImageProc_20190829View.h: CImageProc20190829View 클래스의 인터페이스
//

#pragma once


class CImageProc20190829View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20190829View() noexcept;
	DECLARE_DYNCREATE(CImageProc20190829View)

// 특성입니다.
public:
	CImageProc20190829Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProc20190829View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnTwoImageAdd();
	void LoadTwoImage();
	afx_msg void OnTwoImageSub();
	afx_msg void OnRegionSharpening();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMidFiltering();
};

#ifndef _DEBUG  // ImageProc_20190829View.cpp의 디버그 버전
inline CImageProc20190829Doc* CImageProc20190829View::GetDocument() const
   { return reinterpret_cast<CImageProc20190829Doc*>(m_pDocument); }
#endif

