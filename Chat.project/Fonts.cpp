#include "Fonts.h"

void CreateSegoe_22()
{
	hfSegoe_22 = CreateFont(22, 0, 0, 0, 200, 0, 0, 0, OEM_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS
		, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"Segoe UI");
}