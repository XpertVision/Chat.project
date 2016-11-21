#include "InitHandles.h"

extern LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK LoginEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK LoginPassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK LogonProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern HINSTANCE hInstCopy;
extern HWND hLogButton;
extern HWND hTxt;
extern HWND hLogin;
extern HWND hPass;
extern WNDPROC wpLogin;
extern WNDPROC wpPass;
extern WNDPROC wpLogon;

void InitHandles(HWND hMainWnd)
{
	hLogButton = CreateWindow(L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 296, 340, 48, 48, hMainWnd, (HMENU)ID_LOGON, hInstCopy, NULL);
	hLogin = CreateWindow(L"RICHEDIT", NULL, WS_CHILD | WS_VISIBLE, 220, 191, 200, 20, hMainWnd, (HMENU)123, hInstCopy, NULL);
	hPass = CreateWindow(L"RICHEDIT", NULL, WS_CHILD | WS_VISIBLE | ES_PASSWORD, 220, 271, 200, 20, hMainWnd, NULL, hInstCopy, NULL);

	SendMessage(hLogin, EM_EXLIMITTEXT, NULL, 16);
	SendMessage(hPass, EM_EXLIMITTEXT, NULL, 24);
	SendMessage(hLogin, EM_SETBKGNDCOLOR, NULL, RGB(200, 200, 200));
	SendMessage(hPass, EM_SETBKGNDCOLOR, NULL, RGB(200, 200, 200));

	static wchar_t wFontName[] = L"Segoe UI";

	static CHARFORMAT2W reFormat;
	reFormat.cbSize = sizeof(reFormat);
	reFormat.crTextColor = RGB(24, 65, 233);
	reFormat.bUnderlineType = NULL;
	reFormat.dwMask = CFM_COLOR | CFM_SIZE | CFM_WEIGHT | CFM_FACE;
	reFormat.dwEffects = NULL;
	reFormat.yHeight = 220;
	reFormat.wWeight = 200;
	wcscpy_s(reFormat.szFaceName, sizeof(wFontName), wFontName);

	SendMessage(hLogin, EM_SETCHARFORMAT, SCF_SELECTION, LPARAM(&reFormat));
	SendMessage(hPass, EM_SETCHARFORMAT, SCF_SELECTION, LPARAM(&reFormat));

	wpLogin = (WNDPROC)GetWindowLongPtr(hLogin, GWLP_WNDPROC);
	SetWindowLongPtr(hLogin, GWLP_WNDPROC, (LONG_PTR)LoginEditProc);

	wpPass = (WNDPROC)GetWindowLongPtr(hPass, GWLP_WNDPROC);
	SetWindowLongPtr(hPass, GWLP_WNDPROC, (LONG_PTR)LoginPassProc);

	wpLogon = (WNDPROC)GetWindowLongPtr(hLogButton, GWLP_WNDPROC);
	SetWindowLongPtr(hLogButton, GWLP_WNDPROC, (LONG_PTR)LogonProc);
}