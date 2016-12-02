#include "PlugRiched32.h"

bool PlugRiched32()
{
	HINSTANCE hRTFLib = LoadLibrary(L"MSFTEDIT.dll");

	if (!hRTFLib)
	{
		MessageBox(NULL, L"Msftedit.dll don't load", L"Error", MB_OK);
		return FALSE;
	}

	return TRUE;
}