#include "LogPassChar.h"

wchar_t wchAccesChar[] = { '1','2','3','4','5','6','7','8','9','0',
'q','w','e','r','t','y','u','i','o','p','a','s',
'd','f','g','h','j','k','l','z','x','c','v','b','n','m',
'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F',
'G','H','J','K','L','Z','X','C','V','B','N','M' };

bool search(wchar_t *mass, wchar_t item, int massSize)
{
	for (int i = 0; i < massSize; i++)
	{
		if (mass[i] == item)
		{
			return 1;
		}
	}

	return 0;
}