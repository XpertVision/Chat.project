#ifndef _LOADIMGRES_H_
#define _LOADIMGRES_H_

#include "Header.h"

class LImgRes
{
protected:
	HRSRC hResInfo;
	HANDLE hRes;

	LPVOID lpvResMem;

	DWORD ImgSize;

	void* pvBuff;
	void* cpvResData;
	IStream* pStream;
	Gdiplus::Image* ImgFromRes;
public:
	Gdiplus::Image* GetImg(int RES_ID, HINSTANCE hInst);
	void Release();
};

extern LImgRes SimpleImgLoad;

#endif // !_LOADIMGRES_H_
