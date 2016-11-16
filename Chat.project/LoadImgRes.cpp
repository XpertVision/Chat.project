#include "LoadImgRes.h"

Gdiplus::Image* LImgRes::GetImg(int RES_ID, HINSTANCE hInst)
{
	hResInfo = FindResource(hInst, MAKEINTRESOURCE(RES_ID), RT_RCDATA);
	hRes = LoadResource(hInst, hResInfo);
	lpvResMem = LockResource(hRes);

	ImgSize = SizeofResource(hInst, hResInfo);

	pvBuff = new byte[ImgSize];

	cpvResData = LockResource(LoadResource(hInst, hResInfo));

	memcpy_s(pvBuff, ImgSize, cpvResData, ImgSize);

	CreateStreamOnHGlobal(pvBuff, FALSE, &pStream);

	ImgFromRes = Gdiplus::Image::FromStream(pStream);

	return ImgFromRes;
}

void LImgRes::Release()
{
	if (pvBuff)
		delete pvBuff;
	if (pStream)
		pStream->Release();
	if(ImgFromRes)
		delete ImgFromRes;
	//if (cpvResData)
	//	delete cpvResData;
}

LImgRes SimpleImgLoad;