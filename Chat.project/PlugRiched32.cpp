#include "PlugRiched32.h"

bool PlugRiched32()
{
	HINSTANCE hRTFLib = LoadLibrary(L"RICHED32.DLL");

	if (!hRTFLib)
	{
		MessageBox(NULL, L"RICHED32.DLL don't load", L"Error", MB_OK);
		return FALSE;
	}

	return TRUE;
}