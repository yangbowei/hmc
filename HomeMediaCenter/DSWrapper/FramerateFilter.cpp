#include "StdAfx.h"
#include "FramerateFilter.h"
#include <dvdmedia.h>

FramerateFilter::FramerateFilter(LPUNKNOWN punk, HRESULT * phr, UINT32 fps) : CTransformFilter(L"FramerateFilter", punk, CLSID_NULL), m_fps(fps),
	m_fpsMod(UNITS % fps), m_rtFrameLength(UNITS / fps), m_rtOriginFrameLength(0), m_rtLastFrame(0), m_fpsModSum(0)
{
}

FramerateFilter::~FramerateFilter(void)
{
}

//************* CTransformFilter *************\\

HRESULT FramerateFilter::CheckInputType(const CMediaType * mtIn)
{
	CheckPointer(mtIn, E_POINTER);

	if (!mtIn->bFixedSizeSamples)
		return E_FAIL;

	if (mtIn->majortype != MEDIATYPE_Video)
		return E_FAIL;

	if (mtIn->formattype != FORMAT_VideoInfo && mtIn->formattype != FORMAT_VideoInfo2)
        return E_FAIL;

	//Na zaciatku povoli kazdy video format na vstupe
	//Po pripojeni vystupu sa prepoji na novy format
	return S_OK;
}

HRESULT FramerateFilter::CheckTransform(const CMediaType * mtIn, const CMediaType * mtOut)
{
	CheckPointer(mtIn, E_POINTER);
    CheckPointer(mtOut, E_POINTER);

	//Kontrola vystupneho formatu - ziskaneho pomocou GetMediaType - povoli kazdy
	//Vstupny format sa nekontroluje - bude zmeneny po pripojeni vystupu
	return S_OK;
}

HRESULT FramerateFilter::DecideBufferSize(IMemAllocator * pAlloc, ALLOCATOR_PROPERTIES * pProperties)
{
	CheckPointer(pAlloc, E_POINTER);
    CheckPointer(pProperties, E_POINTER);

    if (this->m_pInput->IsConnected() == FALSE || this->m_pOutput->IsConnected() == FALSE)
        return E_UNEXPECTED;

    HRESULT hr = S_OK;
	ALLOCATOR_PROPERTIES actual;

    pProperties->cBuffers = 1;
    pProperties->cbBuffer = this->m_pOutput->CurrentMediaType().GetSampleSize();

    CHECK_HR(hr = pAlloc->SetProperties(pProperties, &actual));

    if (pProperties->cBuffers > actual.cBuffers || pProperties->cbBuffer > actual.cbBuffer)
		CHECK_HR(hr =  E_FAIL);

done:
	return hr;
}

HRESULT FramerateFilter::GetMediaType(int iPosition, CMediaType * pMediaType)
{
	HRESULT hr = S_OK;
	int actPos = 0;

	AM_MEDIA_TYPE * mediaType = NULL;
	IEnumMediaTypes * enumTypes = NULL;

	IPin * conPin = this->m_pInput->GetConnected();
	if (conPin == NULL)
		CHECK_HR(hr = E_UNEXPECTED);

	CHECK_HR(hr = conPin->EnumMediaTypes(&enumTypes));
	CHECK_HR(hr = enumTypes->Reset());

	while (enumTypes->Next(1, &mediaType, NULL) == S_OK)
	{
		if (mediaType->formattype == FORMAT_VideoInfo || mediaType->formattype == FORMAT_VideoInfo2)
		{
			if (actPos == iPosition)
			{
				CHECK_HR(hr = CopyMediaType(pMediaType, mediaType));

				if (pMediaType->formattype == FORMAT_VideoInfo)
				{
					VIDEOINFOHEADER * header = (VIDEOINFOHEADER *)pMediaType->pbFormat;
					this->m_rtOriginFrameLength = header->AvgTimePerFrame;
					header->AvgTimePerFrame = this->m_rtFrameLength;
				}
				else
				{
					VIDEOINFOHEADER2 * header = (VIDEOINFOHEADER2 *)pMediaType->pbFormat;
					this->m_rtOriginFrameLength = header->AvgTimePerFrame;
					header->AvgTimePerFrame = this->m_rtFrameLength;
				}
				goto done;
			}

			actPos++;
		}

		DeleteMediaType(mediaType);
		mediaType = NULL;
	}

	hr = VFW_S_NO_MORE_ITEMS;

done:

	DeleteMediaType(mediaType);
	SAFE_RELEASE(enumTypes);

	return hr;
}

HRESULT FramerateFilter::CompleteConnect(PIN_DIRECTION direction, IPin * pReceivePin)
{
	HRESULT hr = S_OK;
	IPin * conPin = NULL;

	AM_MEDIA_TYPE pmt;
	pmt.cbFormat = 0;
	pmt.pUnk = NULL;

	if (direction == PINDIR_OUTPUT)
	{
		//Ak je pripojeny vystup, nastavi sa vstup podla neho
		CHECK_HR(hr = pReceivePin->ConnectionMediaType(&pmt));
		
		conPin = this->m_pInput->GetConnected();
		if (conPin == NULL)
			CHECK_HR(hr = E_FAIL);

		if (pmt.formattype == FORMAT_VideoInfo)
		{
			VIDEOINFOHEADER * header = (VIDEOINFOHEADER *)pmt.pbFormat;
			header->AvgTimePerFrame = this->m_rtOriginFrameLength;
		}
		else
		{
			VIDEOINFOHEADER2 * header = (VIDEOINFOHEADER2 *)pmt.pbFormat;
			header->AvgTimePerFrame = this->m_rtOriginFrameLength;
		}

		hr = conPin->QueryAccept(&pmt);
		if (hr == S_OK)
		{
			CHECK_HR(hr = ReconnectPin(conPin, &pmt));
		}
		else
		{
			CHECK_HR(hr = E_FAIL);
		}
	}

done:

	FreeMediaType(pmt);

	return hr;
}

HRESULT FramerateFilter::Receive(IMediaSample * pSample)
{
	CheckPointer(pSample, E_POINTER);

	HRESULT hr = S_OK;
    BYTE * pSourceBuffer, * pDestBuffer;
	REFERENCE_TIME rtOldStart, rtOldStop;
	IMediaSample * pOut = NULL;
    long longVal; 

	longVal = pSample->GetActualDataLength();
	CHECK_HR(hr = pSample->GetPointer(&pSourceBuffer));
	CHECK_HR(hr = pSample->GetTime(&rtOldStart, &rtOldStop));

	//Snimka sa bude opakovat, pokial nedosiahne povodnu casovu peciatku
	while (this->m_rtLastFrame + this->m_rtFrameLength <= rtOldStop)
	{
		CHECK_HR(hr = InitializeOutputSample(pSample, &pOut));

		REFERENCE_TIME rtStart = this->m_rtLastFrame;
		REFERENCE_TIME rtStop  = rtStart + this->m_rtFrameLength;

		//Do uvahy sa bere aj desatinna cast - ak presiahne 1 a viac
		this->m_fpsModSum += m_fpsMod;
		rtStop += (this->m_fpsModSum / m_fps);
		this->m_fpsModSum %= m_fps;

		CHECK_HR(hr = pOut->SetTime(&rtStart, &rtStop));
		this->m_rtLastFrame = rtStop;

		//Skopirovat data zo vstupneho buffera do vystupneho
		CHECK_HR(hr = pOut->GetPointer(&pDestBuffer));
		CopyMemory((void *)pDestBuffer, (void *)pSourceBuffer, longVal);

		CHECK_HR(hr = this->m_pOutput->Deliver(pOut));

		SAFE_RELEASE(pOut);
	}

done:

	SAFE_RELEASE(pOut);

	return hr;
}