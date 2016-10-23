#include "Header.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoginEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;
HWND hLogWnd;
HWND hTxt;
HWND hLogin;
HWND hPass;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hRTFLib;
	hRTFLib = LoadLibrary(L"RICHED32.DLL");

	if (!hRTFLib)
	{
		MessageBox(NULL, L"RICHED32.DLL don't load", L"Error", MB_OK);
		return 1;
	}

	MSG mMessage;
	HWND hMainWnd;

	TCHAR mainWndClassName[] = L"Chat.project";

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	WNDCLASSEX wMainClass;
	ZeroMemory(&wMainClass, sizeof(wMainClass));

	wMainClass.cbSize        = sizeof(wMainClass);
	wMainClass.hInstance     = hInst;
	wMainClass.lpfnWndProc   = MainWndProc;
	wMainClass.lpszClassName = mainWndClassName;
	wMainClass.cbClsExtra    = NULL;
	wMainClass.cbWndExtra    = NULL;
	wMainClass.hbrBackground = CreateSolidBrush(RGB(4, 37, 65));
	wMainClass.style         = CS_VREDRAW | CS_HREDRAW;
	wMainClass.hIcon         = LoadIcon(hInst, MAKEINTRESOURCE(ID_MAIN_ICO));
	wMainClass.hIconSm       = LoadIcon(hInst, MAKEINTRESOURCE(ID_SMALL_ICO));
	wMainClass.hCursor       = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&wMainClass))
	{
		MessageBox(NULL, L"Window class don't register", L"Error", MB_OK);
		return 1;
	}

	hMainWnd = CreateWindowEx(NULL, mainWndClassName, L"Chat.project", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480, NULL, NULL, hInst, NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, L"Window don't create", L"Error", MB_OK);
		return 1;
	}

	hLogWnd = CreateWindow(L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 296, 340, 48, 48, hMainWnd, (HMENU)ID_LOGON, hInst, NULL);
	hLogin = CreateWindow(L"RICHEDIT", NULL, WS_CHILD | WS_VISIBLE, 220, 191, 200, 20, hMainWnd, (HMENU)123, hInst, NULL);
	hPass = CreateWindow(L"RICHEDIT", NULL, WS_CHILD | WS_VISIBLE | ES_PASSWORD, 220, 271, 200, 20, hMainWnd, NULL, hInst, NULL);

	SendMessage(hLogin, EM_EXLIMITTEXT, NULL, 16);
	SendMessage(hPass, EM_EXLIMITTEXT, NULL, 24);
	SendMessage(hLogin, EM_SETBKGNDCOLOR, NULL, RGB(200, 200, 200));
	SendMessage(hPass, EM_SETBKGNDCOLOR, NULL, RGB(200, 200, 200));
	
	wchar_t wFontName [] = L"Segoe UI";

	CHARFORMAT2W reFormat;
	reFormat.cbSize = sizeof(reFormat);
	reFormat.crTextColor = RGB(24,65,233);
	reFormat.bUnderlineType = NULL;
	reFormat.dwMask = CFM_COLOR | CFM_SIZE | CFM_WEIGHT | CFM_FACE;
	reFormat.dwEffects = NULL;
	reFormat.yHeight = 220;
	reFormat.wWeight = 200;
	wcscpy_s(reFormat.szFaceName, sizeof(wFontName), wFontName);

	SendMessage(hLogin, EM_SETCHARFORMAT, SCF_SELECTION, LPARAM(&reFormat));
	SendMessage(hPass, EM_SETCHARFORMAT, SCF_SELECTION, LPARAM(&reFormat));
	
	//SetWindowLongPtr(hLogin, GWLP_WNDPROC, (LONG_PTR)LoginEditProc);

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	while (GetMessage(&mMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&mMessage);
		DispatchMessage(&mMessage);
	}

	return mMessage.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdcMain;
	PAINTSTRUCT pstMain;
	//RECT rMain(NULL);

	LPDRAWITEMSTRUCT lpdrawstLogon = NULL;
	//HDC hdcLogon;

	HFONT hfSegoe = CreateFont(22, 0, 0, 0, 200, 0, 0, 0, OEM_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS
		, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"Segoe UI");

	LPMINMAXINFO pInfo = NULL;
	POINT StartWndSize;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		hdcMain = GetDC(0);
		int x, y;
		x = GetDeviceCaps(hdcMain, HORZRES);
		y = GetDeviceCaps(hdcMain, VERTRES);
		SetWindowPos(hWnd, NULL, ((x - 640) / 2), ((y - 480) / 2), 0, 0, SWP_NOSIZE);
		ReleaseDC(0, hdcMain);
	}
	break;
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case 567:
		{
			MessageBeep(TRUE);
		}
		break;
		default: break;
		}
		break;
	case WM_PAINT:
	{
		hdcMain = BeginPaint(hWnd, &pstMain);

		Gdiplus::Graphics gdiGrLogo(hdcMain);
		Gdiplus::Image *gdiImgLogo = new Gdiplus::Image(L"Logo.png");

		SetTextColor(hdcMain, RGB(200, 200, 200));
		SetBkColor(hdcMain, RGB(4, 37, 65));

		SelectObject(hdcMain, hfSegoe);

		SetTextAlign(hdcMain, TA_RIGHT);
		TextOutW(hdcMain, 210, 270, L"Password", 8);
		TextOutW(hdcMain, 210, 190, L"Login", 5);
		SetTextAlign(hdcMain, TA_LEFT);

		gdiGrLogo.DrawImage(gdiImgLogo, 256, 40, 128, 128);
		delete gdiImgLogo;

		EndPaint(hWnd, &pstMain);
	}
	break;
	case WM_DRAWITEM:
	{
		lpdrawstLogon = (LPDRAWITEMSTRUCT)lParam;

		if (lpdrawstLogon->hwndItem == hLogWnd)
		{
			FillRect(lpdrawstLogon->hDC, &lpdrawstLogon->rcItem, CreateSolidBrush(RGB(4, 37, 65)));

			Gdiplus::Graphics gdiGrLogon(lpdrawstLogon->hDC);
			Gdiplus::Image *gdiImgLogon = new Gdiplus::Image(L"LogonDef.png");
			gdiGrLogon.DrawImage(gdiImgLogon, 0, 0, 48, 48);
			delete gdiImgLogon;

			switch (lpdrawstLogon->CtlID)
			{
			case ID_LOGON:
			{
				if (lpdrawstLogon->itemState & ODS_SELECTED)
				{
					FillRect(lpdrawstLogon->hDC, &lpdrawstLogon->rcItem, CreateSolidBrush(RGB(4, 37, 65)));
					gdiImgLogon = new Gdiplus::Image(L"LogonClick.png");
					gdiGrLogon.DrawImage(gdiImgLogon, 0, 0, 48, 48);
					delete gdiImgLogon;
					SendMessage(hWnd, WM_COMMAND, 567, NULL);
				}
				else if (lpdrawstLogon->itemState & ODS_FOCUS)
				{
					FillRect(lpdrawstLogon->hDC, &lpdrawstLogon->rcItem, CreateSolidBrush(RGB(4, 37, 65)));
					gdiImgLogon = new Gdiplus::Image(L"LogonSet.png");
					gdiGrLogon.DrawImage(gdiImgLogon, 0, 0, 48, 48);
					delete gdiImgLogon;
				}
			}
			break;
			}
		}
	}
	break;
	case WM_SETCURSOR:
	{
		static HWND hFocused(NULL);
		if (hLogWnd == (HWND)wParam)
		{
			if (GetFocus() != hLogWnd)
			{
				hFocused = GetFocus();
				SetFocus(hLogWnd);
			}
		}
		else
		{
			if (GetFocus() == hLogWnd)
			{
				SetFocus(hFocused);
			}
		}
		DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	break;
	case WM_GETMINMAXINFO:
	{
		pInfo = (LPMINMAXINFO)lParam;
		StartWndSize = { 640, 480 };
		pInfo->ptMinTrackSize = StartWndSize;
		pInfo->ptMaxTrackSize = StartWndSize;
		return 0;
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return NULL;
	}
}

LRESULT CALLBACK LoginEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	/*case WM_COMMAND:
	{
		if (HIWORD(wParam) == EN_CHANGE)
		{
			MessageBeep(TRUE);
		}
	}
	break;*/
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);;
	}

	return 0;
}