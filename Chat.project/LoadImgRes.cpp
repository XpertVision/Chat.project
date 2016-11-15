#include "LoadImgRes.h"

Gdiplus::Image* LImgRes::GetImg(int RES_ID, HINSTANCE hInst)
{
	hResInfo = FindResource(hInst, MAKEINTRESOURCE(RES_ID), RT_RCDATA);
	hRes = LoadResource(hInst, hResInfo);
	lpvResMem = LockResource(hRes);
	ImgSize = SizeofResource(hInst, hResInfo);
	cpvResData = LockResource(LoadResource(hInst, hResInfo));
	CreateStreamOnHGlobal(cpvResData, FALSE, &pStream);

	//ImgFromRes = 0;
	ImgFromRes = Gdiplus::Image::FromStream(pStream);

	return ImgFromRes;
}