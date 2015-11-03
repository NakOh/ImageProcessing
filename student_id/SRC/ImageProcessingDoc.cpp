
// ImageProcessingDoc.cpp : Implement a CImageProcessingDoc Class
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "DlgBrightnessOption.h"
#include "DlgMosaicOption.h"
#include "DlgCompositeOption.h"
#include "DlgIntensityTransformOption.h"
#include "DlgContrastStretchOption.h"

#include "ImageProcessingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_PROCESS_MOSAIC, &CImageProcessingDoc::OnProcessMosaic)
	ON_COMMAND(ID_PROCESS_BRIGHTNESS, &CImageProcessingDoc::OnProcessBrightness)
	ON_COMMAND(ID_PROCESS_COMPOSITE, &CImageProcessingDoc::OnProcessComposite)
	ON_COMMAND(ID_PROCESS_INTENSITY_TRANSFORM, &CImageProcessingDoc::OnProcessIntensityTransform)
	ON_COMMAND(ID_PROCESS_CONTRAST_STRETCH, &CImageProcessingDoc::OnProcessContrastStretch)
	ON_COMMAND(ID_PROCESS_EQUALIZATION, &CImageProcessingDoc::OnProcessEqualization)
	ON_COMMAND(ID_32783, &CImageProcessingDoc::OnHistogramSpecification)
END_MESSAGE_MAP()


// CImageProcessingDoc Contruction/Destuction

CImageProcessingDoc::CImageProcessingDoc()
{
	//// TODO: Add an one-time generating code here
	m_pImage = NULL;
}

CImageProcessingDoc::~CImageProcessingDoc()
{
	if (NULL != m_pImage)
		delete m_pImage;
}

BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: load imagefile // DONE
	m_pImage = new CxImage;
	m_pImage->Load(lpszPathName, FindType(lpszPathName));

	CalculateHistogram();

	return TRUE;
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//// TODO: Add a re-initialization code here
	//// SDI documents will reuse this article

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//// TODO: Add a saving code here
	}
	else
	{
		//// TODO: Add a loading code here
	}
}


// CImageProcessingDoc diagnosis

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc command

CString CImageProcessingDoc::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}

CString CImageProcessingDoc::RemoveExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(0,i);
		}
	}
	return name;
}

int CImageProcessingDoc::FindType(const CString& ext)
{
	return CxImage::GetTypeIdFromName(ext);
}

void CImageProcessingDoc::CalculateHistogram()
{
	// TODO: Add a calculating histogram code here
	if (m_pImage) {
		// Histogram function, which is implemented in Cximage
		 //m_histogramMax = m_pImage->Histogram(m_histogramRed, m_histogramGreen, m_histogramBlue, m_histogramGray);

		RGBQUAD color;

		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();

		for (int i = 0; i < 256; i++){
			m_histogramRed[i] = 0;
			m_histogramGreen[i] =0;
			m_histogramBlue[i] = 0;
			m_histogramGray[i] = 0;
		}


		for (DWORD y = 0; y < height; y++) {
			for (DWORD x = 0; x < width; x++) {
				color = m_pImage->GetPixelColor(x, y);

				m_histogramRed[color.rgbRed] += 1;
				m_histogramGreen[color.rgbGreen] += 1;
				m_histogramBlue[color.rgbBlue] += 1;
				m_histogramGray[(color.rgbRed + color.rgbGreen + color.rgbBlue) / 3] += 1;
			}
		}
		// 가짜코드
	

		m_histogramMax = 0;
		for (int i = 0; i < 256; i++){
			m_histogramMax = max(m_histogramMax, m_histogramRed[i]  );
			m_histogramMax = max(m_histogramMax, m_histogramGreen[i]);
			m_histogramMax = max(m_histogramMax, m_histogramBlue[i] );
			m_histogramMax = max(m_histogramMax, m_histogramGray[i] );
		}

		//////////////////////////////////////////////////////////////
	}
}

void CImageProcessingDoc::OnProcessBrightness()
{
	// TODO: Add a changing the brightness histogram code here
	if (m_pImage) {
		DlgBrightnessOption dlg;

		if (dlg.DoModal() == IDOK) {
			// write your own code
			// for applying your effect, you must use m_pImage	
			// this code is a simple example for manufacturing image : grayscaling

			int nPlusMinus = dlg.m_nPlusMinus;
			BYTE byModifyValue = dlg.m_byModifyValue;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;



			if (nPlusMinus){
				//나누기
				for (DWORD y = 0; y < height; y++) {
					for (DWORD x = 0; x < width; x++) {
						color = m_pImage->GetPixelColor(x, y);

						int blue = color.rgbBlue / 2;
						int green = color.rgbGreen / 2;
						int red = color.rgbRed / 2;

						if (blue > 255){ blue = 255; }
						if (green > 255){ green = 255; }
						if (red > 255){ red = 255; }

						if (blue < 0){ blue = 0; }
						if (green< 0){ green = 0; }
						if (red < 0){ red = 0; }


						newcolor.rgbRed = (BYTE)red;
						newcolor.rgbBlue = (BYTE)blue;
						newcolor.rgbGreen = (BYTE)green;
						m_pImage->SetPixelColor(x, y, newcolor);
					}
				}

			}
			else{
				//곱하기
				for (DWORD y = 0; y < height; y++) {
					for (DWORD x = 0; x < width; x++) {
						color = m_pImage->GetPixelColor(x, y);

						int blue = color.rgbBlue * 2;
						int green = color.rgbGreen * 2;
						int red = color.rgbRed * 2;

						if (blue > 255){ blue = 255; }
						if (green > 255){ green = 255; }
						if (red > 255){ red = 255; }

						if (blue < 0){ blue = 0; }
						if (green< 0){ green = 0; }
						if (red < 0){ red = 0; }


						newcolor.rgbRed = (BYTE)red;
						newcolor.rgbBlue = (BYTE)blue;
						newcolor.rgbGreen = (BYTE)green;
						m_pImage->SetPixelColor(x, y, newcolor);
					}
				}
			}

			/*
			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					color = m_pImage->GetPixelColor(x, y);

					int blue = color.rgbBlue;
					int green = color.rgbGreen;
					int red = color.rgbRed;

					if (nPlusMinus){
						blue -= byModifyValue;
						green -= byModifyValue;
						red -= byModifyValue;
					}
					else{
						blue += byModifyValue;
						green += byModifyValue;
						red += byModifyValue;
					}

					if (blue > 255){ blue = 255; }
					if (green > 255){ green = 255; }
					if (red > 255){ red = 255; }

					if (blue < 0){ blue= 0; }
					if (green< 0){ green = 0; }
					if (red < 0){  red = 0; }

					newcolor.rgbBlue = (BYTE)blue;
					newcolor.rgbRed = (BYTE)red;
					newcolor.rgbGreen = (BYTE)green;

					m_pImage->SetPixelColor(x, y, newcolor);
				}
			}

			*/
			// code to view overflow, Keep observation with the debugger
			BYTE a = 255;
			BYTE b = 1;
			int  c = 10;
			BYTE r;

			r = a + b;
			r = a + c;
			r = b + c;
		}
	}
	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessMosaic()
{
	// TODO: Add a mosaic code here
	if (m_pImage) {
		DlgMosaicOption dlg;

		if (dlg.DoModal() == IDOK) {
			// write your own code
			// for applying your effect, you must use m_pImage
			// this code is a simple example for manufacturing image : grayscaling


			DWORD dwWindowSize = dlg.m_dwWindowSize;
			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;

			if (dwWindowSize == 0){
				//Blurring
				float mask[3][3] = { { 1, 1, 1 },
									 { 1, 1, 1 },
									 { 1, 1, 1 } };
				


				CxImage* buffer = new CxImage;
				buffer->Create(width, height, 24, CXIMAGE_FORMAT_BMP);

				int sumRed = 0;
				int sumGreen = 0;
				int sumBlue = 0;

				for (int xsize = 0; xsize < width-2; xsize++){
					for (int ysize = 0; ysize < height-2; ysize++){
						sumRed = 0;
						sumGreen = 0;
						sumBlue = 0;
						for (int x = xsize; x < (xsize + 3); x++){
							for (int y = ysize; y < (ysize + 3); y++){
								color = m_pImage->GetPixelColor(x, y);
								sumBlue += color.rgbBlue * mask[x - xsize][y - ysize];
								sumRed += color.rgbRed * mask[x - xsize][y - ysize];
								sumGreen += color.rgbGreen * mask[x - xsize][y - ysize];
							}
						}

						sumBlue = sumBlue / 9;
						sumGreen = sumGreen / 9;
						sumRed = sumRed / 9;

						newcolor.rgbBlue = (BYTE)sumBlue;
						newcolor.rgbRed = (BYTE)sumRed;
						newcolor.rgbGreen = (BYTE)sumGreen;

						buffer->SetPixelColor(xsize + 1, ysize + 1, newcolor);
					}
				}

				for (int xsize = 1; xsize < width-1; xsize++){
					for (int ysize = 1; ysize < height-1; ysize++){
						m_pImage->SetPixelColor(xsize, ysize, buffer->GetPixelColor(xsize,ysize));
					}
				}
				
			}
			else if (dwWindowSize == 1){
				//Sharpening
				float mask[3][3] = { { 0, -1, 0 },
									{ -1, 5, -1	 },
									{ 0, -1, 0 } };



				CxImage* buffer = new CxImage;
				buffer->Create(width, height, 24, CXIMAGE_FORMAT_BMP);

				int sumRed = 0;
				int sumGreen = 0;
				int sumBlue = 0;

				for (int xsize = 0; xsize < width - 2; xsize++){
					for (int ysize = 0; ysize < height - 2; ysize++){
						sumRed = 0;
						sumGreen = 0;
						sumBlue = 0;
						for (int x = xsize; x < (xsize + 3); x++){
							for (int y = ysize; y < (ysize + 3); y++){
								color = m_pImage->GetPixelColor(x, y);
								sumBlue += color.rgbBlue * mask[x - xsize][y - ysize];
								sumRed += color.rgbRed * mask[x - xsize][y - ysize];
								sumGreen += color.rgbGreen * mask[x - xsize][y - ysize];
							}
						}

						sumBlue = sumBlue;
						sumGreen = sumGreen;
						sumRed = sumRed;

						if (sumBlue < 0){
							sumBlue = 0;
						}

						if(sumGreen < 0){
							sumGreen = 0;
						}

						if (sumRed < 0){
							sumRed = 0;
						}

						if (sumBlue >255){
							sumBlue = 255;
						}
						if (sumGreen >255){
							sumGreen = 255;
						}
						if (sumRed >255){
							sumRed = 255;
						}
						newcolor.rgbBlue = (BYTE)sumBlue;
						newcolor.rgbRed = (BYTE)sumRed;
						newcolor.rgbGreen = (BYTE)sumGreen;

						buffer->SetPixelColor(xsize + 1, ysize + 1, newcolor);
					}
				}

				for (int xsize = 1; xsize < width - 1; xsize++){
					for (int ysize = 1; ysize < height - 1; ysize++){
						m_pImage->SetPixelColor(xsize, ysize, buffer->GetPixelColor(xsize, ysize));
					}
				}
			}
			else{
				//Mosaic
			

				DWORD windowSize = dwWindowSize * dwWindowSize;

				int ystep = height / dwWindowSize;
				int xstep = width / dwWindowSize;

				int blue = 0;
				int green = 0;
				int red = 0;

				int newBlue = 0;
				int newGreen = 0;
				int newRed = 0;

				int ysize = 0;
				int xsize = 0;

				for (ysize = 0; ysize < height; ysize += dwWindowSize){
					for (xsize = 0; xsize < width; xsize += dwWindowSize){
						for (DWORD y = ysize; y < (ysize + dwWindowSize); y++) {
							for (DWORD x = xsize; x < (xsize + dwWindowSize); x++) {
								color = m_pImage->GetPixelColor(x, y);
								blue += color.rgbBlue;
								green += color.rgbGreen;
								red += color.rgbRed;
							}
						}
						newBlue = (int)(blue / windowSize);
						newGreen = (int)(green / windowSize);
						newRed = (int)(red / windowSize);
						newcolor.rgbBlue = (BYTE)newBlue;
						newcolor.rgbGreen = (BYTE)newGreen;
						newcolor.rgbRed = (BYTE)newRed;
						for (DWORD y = ysize; y < (ysize + dwWindowSize); y++) {
							for (DWORD x = xsize; x < (xsize + dwWindowSize); x++) {
								m_pImage->SetPixelColor(x, y, newcolor);
							}

						}
						blue = 0;
						green = 0;
						red = 0;
					}
					if (xsize>width){
						for (DWORD y = ysize; y < (ysize + dwWindowSize); y++) {
							for (DWORD x = width; x >(width - dwWindowSize); x--) {
								color = m_pImage->GetPixelColor(x, y);
								blue += color.rgbBlue;
								green += color.rgbGreen;
								red += color.rgbRed;
							}
						}
						newBlue = (int)(blue / windowSize);
						newGreen = (int)(green / windowSize);
						newRed = (int)(red / windowSize);
						newcolor.rgbBlue = (BYTE)newBlue;
						newcolor.rgbGreen = (BYTE)newGreen;
						newcolor.rgbRed = (BYTE)newRed;
						for (DWORD y = ysize; y < (ysize + dwWindowSize); y++) {
							for (DWORD x = width; x >(width - dwWindowSize); x--) {
								m_pImage->SetPixelColor(x, y, newcolor);
							}

						}
						blue = 0;
						green = 0;
						red = 0;
					}
				}
				if (ysize > height){
					for (DWORD y = height; y < (height - dwWindowSize); y++) {
						for (DWORD x = xsize; x < (xsize + dwWindowSize); x++) {
							color = m_pImage->GetPixelColor(x, y);
							blue += color.rgbBlue;
							green += color.rgbGreen;
							red += color.rgbRed;
						}
					}
					newBlue = (int)(blue / windowSize);
					newGreen = (int)(green / windowSize);
					newRed = (int)(red / windowSize);
					newcolor.rgbBlue = (BYTE)newBlue;
					newcolor.rgbGreen = (BYTE)newGreen;
					newcolor.rgbRed = (BYTE)newRed;
					for (DWORD y = ysize; y < (height - dwWindowSize); y++) {
						for (DWORD x = xsize; x < (xsize + dwWindowSize); x++) {
							m_pImage->SetPixelColor(x, y, newcolor);
						}

					}
					blue = 0;
					green = 0;
					red = 0;
				}
			}
	
		
	}
			
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessComposite()
{
	// TODO: Add a composite code here
	if (m_pImage) {
		DlgCompositeOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nOperatorID = dlg.GetCompositeOperatorID();
			CxImage * pSecondImage = dlg.GetSecondImage();

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD firstColor;
			RGBQUAD secondColor;
			RGBQUAD newColor;;



			if (nOperatorID == 0){
				//add Function
				for (DWORD y = 0; y < height; y++) {
					for (DWORD x = 0; x < width; x++) {
						firstColor = m_pImage->GetPixelColor(x, y);
						secondColor = pSecondImage->GetPixelColor(x, y);
							
							int blue = firstColor.rgbBlue +secondColor.rgbBlue;
							int green = firstColor.rgbGreen + secondColor.rgbGreen;
							int red = firstColor.rgbRed + secondColor.rgbRed;

							if (blue > 255){ blue = 255; }
							if (green > 255){ green = 255; }
							if (red > 255){ red = 255; }

							if (blue < 0){ blue = 0; }
							if (green< 0){ green = 0; }
							if (red < 0){ red = 0; }

							newColor.rgbRed = (BYTE)red;
							newColor.rgbBlue = (BYTE)blue;
							newColor.rgbGreen = (BYTE)green;
						
						
						m_pImage->SetPixelColor(x, y, newColor);
					}
				}
			}
			else{
				//Substract Function
				for (DWORD y = 0; y < height; y++) {
					for (DWORD x = 0; x < width; x++) {
						firstColor = m_pImage->GetPixelColor(x, y);
						secondColor = pSecondImage->GetPixelColor(x, y);

						int blue = firstColor.rgbBlue - secondColor.rgbBlue;
						int green = firstColor.rgbGreen - secondColor.rgbGreen;
						int red = firstColor.rgbRed - secondColor.rgbRed;

						if (blue > 255){ blue = 255; }
						if (green > 255){ green = 255; }
						if (red > 255){ red = 255; }

						if (blue < 0){ blue = 0; }
						if (green< 0){ green = 0; }
						if (red < 0){ red = 0; }

						newColor.rgbRed = (BYTE)red;
						newColor.rgbBlue = (BYTE)blue;
						newColor.rgbGreen = (BYTE)green;


						m_pImage->SetPixelColor(x, y, newColor);
					}
				}
			}
			
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessIntensityTransform()
{
	// TODO: Add a Contrast conversion code here
	if (m_pImage) {
		DlgIntensityTransformOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nTransformType = dlg.m_nTransformType;
			double nLinearTransfromCoefficient_a = dlg.m_nLinearTransfromCoefficient_a;
			double nLinearTransfromCoefficient_b = dlg.m_nLinearTransfromCoefficient_b;

			int byThresholdValue = dlg.m_byThresholdValue;

			BYTE byContrastStretching_Start = dlg.m_byContrastStretching_Start;
			BYTE byContrastStretching_End = dlg.m_byContrastStretching_End;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessContrastStretch()
{
	// TODO: Add a Contrast stretching code here
	if (m_pImage) {
		DlgContrastStretchOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nStretchType = dlg.m_nStretchType;
			float fLow = dlg.m_fLow;
			float fHigh = dlg.m_fHigh;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;
			
			BYTE LUT[256];

			// initialize thresholds
			int nLowTherhs = 0;
			int nHighThresh = 255;


			// compute thresholds
			if (nStretchType == 0) { // Auto
				for (int i = 0; i < 256; i++){
					if (m_histogramGray[i]!=0){
						nLowTherhs = i;
						break;
					}					
				}
				for (int i = 255; i > -1; i--){
					if (m_histogramGray[i] != 0){
						nHighThresh = i;
						break;
					}
				}
				
			} else if (nStretchType == 1) { // Ends-In

				for (int i = 0; i < 256; i++){
					if (m_histogramGray[i] >= fLow){
						nLowTherhs = i;
						break;
					}
				}
				for (int i = 255; i > -1; i--){
					if (m_histogramGray[i] <= fHigh){
						nHighThresh = i;
						break;
					}
				}
				nLowTherhs = fLow;
				nHighThresh = fHigh;
			}

			if (nLowTherhs < 0){
				nLowTherhs = 0;
			}

			if (nLowTherhs > 255){
				nLowTherhs = 255;
			}
			if (nHighThresh < 0){
				nHighThresh = 0;
			}if (nHighThresh > 255){
				nHighThresh = 255;
			}

			// compute LUT
			for (int i = 0; i < 255; i++){
				if (i <= nLowTherhs){
					LUT[i] = 0;
				}
				else if (nLowTherhs <= i  && i <= nHighThresh){
					LUT[i] = 255 * (i - nLowTherhs) / (nHighThresh - nLowTherhs);
				}
				else if(nHighThresh <= i){
					LUT[i] = 255;
				}
				
			}

			// trnasfer image
			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					color = m_pImage->GetPixelColor(x, y);
					newcolor.rgbBlue = LUT[color.rgbBlue];
					newcolor.rgbGreen = LUT[color.rgbGreen];
					newcolor.rgbRed = LUT[color.rgbRed];
					
					m_pImage->SetPixelColor(x, y, newcolor);
				}
			}
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessEqualization()
{
	// TODO: Add a Histogram equalization code here
	if (m_pImage) 
	{

		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();
		RGBQUAD color;	// Save the current color value
		RGBQUAD newcolor;	// After the conversion, save the color value
		//(1) Histogram has already been generated histogram(Omission) 
		//(2) Create a cumulative histogram
		DWORD sum = 0;
		float scale_factor = 255.0 / (width*height);
		DWORD sum_hist[256]; // a normalized histogram

		for(int i=0; i<256 ; i++)
		{
			sum += m_histogramGray[i];
			sum_hist[i] = sum;

		}
		

		//(3) Calculating look-up table
		BYTE LUT[256]; // look-up table

		for(int i=0; i<256 ; i++)
		{
		// (Coding)  
			LUT[i] = sum_hist[i] * scale_factor;
		}

		// (4) Image Conversion
		for (DWORD y = 0; y < height; y++) 
		{
			for (DWORD x = 0; x < width; x++) 
			{
				color = m_pImage->GetPixelColor(x, y);
				// (Coding)
				int blue = LUT[color.rgbBlue];
				int green = LUT[color.rgbGreen];
				int red = LUT[color.rgbRed];

				if (blue > 255){ blue = 255; }
				if (green > 255){ green = 255; }
				if (red > 255){ red = 255; }

				if (blue < 0){ blue = 0; }
				if (green< 0){ green = 0; }
				if (red < 0){ red = 0; }

				newcolor.rgbRed = (BYTE)red;
				newcolor.rgbBlue = (BYTE)blue;
				newcolor.rgbGreen = (BYTE)green;



				m_pImage->SetPixelColor(x, y, newcolor);
			}
		}		
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}



void CImageProcessingDoc::OnHistogramSpecification()
{
	// TODO: Add a Histogram specifications code here
	if (m_pImage) 
	{

		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();
		RGBQUAD color;	// Save the current color value
		RGBQUAD newcolor;	// After the conversion, save the color value

		//(1) Histogram has already been generated histogram(Omission) 
		//(2) Create a cumulative histogram
		DWORD sum = 0;
		float scale_factor = 255.0 / (width*height);
		DWORD sum_hist[256]; // a cumulative histogram

		for(int i=0; i<256 ; i++)
		{
		// (coding)

		}


		//(3) Calculating look-up table
		BYTE LUT[256]; // look-up table

		for(int i=0; i<256 ; i++)
		{
		// (coding)  


		}


		// Same as histogram equalization code from here.
		// However, After a cumulative histogram convert to float sum_hist[256] and
		// modifing to be entered in the real number on calculating sum_hist


		//(4) 
		DWORD desired_histogram[256];
		// Making desired_histogram
/*
		//1.
		for (int i=0; i<=255; i++)
		{
			desired_histogram[i]=i;
		}
*/
/*
		//2.
		for (int i=0; i<=255; i++)
		{
			desired_histogram[i]=255-i;
		}
*/
/*
		//3.		
		for (int i=0; i<=127; i++)
		{
			desired_histogram[i]=127-i;
		}
		for (int i=128; i<=255; i++)
		{
			desired_histogram[i]=i-127;
		}
*/

		// redefinition
		sum = 0;
		scale_factor = 255.0 / (width*height);

		//(5) Create the cumulative histogram of histogram you want
		for(int i=0; i<256; i++)
		{
			//(coding)



		}

		//(6) Is the inverse.
		float difference;	// calculate the difference
		int min;	// Calculate the minimum of the difference
		DWORD inv_hist[256];	// reverse-histogram

		//(Hint) will use dual-route.
		// float fabs() Use library functions.
		for(int i=0; i<256; i++)
		{
		//(coding)




		}

		//(7) Create look-up table of reverse-histogram
		for(int i=0; i<256 ; i++)
		{
		//(coding)

		}
		
		

		// (8) Image Conversion
		for (DWORD y = 0; y < height; y++) 
		{
			for (DWORD x = 0; x < width; x++) 
			{
				color = m_pImage->GetPixelColor(x, y);
				// (coding)



				m_pImage->SetPixelColor(x, y, newcolor);
			}
		}		
	} // if(m_pImage)

	CalculateHistogram();
	UpdateAllViews(NULL);

	

}
