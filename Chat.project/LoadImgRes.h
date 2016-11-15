//#include "Header.h"

#include <Windows.h>
#include <gdiplus.h>

#ifndef _LOADIMGRES_H_
#define _LOADIMGRES_H_

class LImgRes
{
protected:
	HRSRC hResInfo;
	HANDLE hRes;

	LPVOID lpvResMem;

	DWORD ImgSize;

	//void* pvBuff;
	void* cpvResData;
	IStream* pStream;
	Gdiplus::Image* ImgFromRes;
public:
	Gdiplus::Image* GetImg(int RES_ID, HINSTANCE hInst);
	/*void Release();*/
};

#endif // !_LOADIMGRES_H_
