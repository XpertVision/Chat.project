#include "Header.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR lpCmdLine, int nCmdShow)
{
	GdiPlusInit();

	if (!PlugRiched32())
		return 1;

	CreateSegoe_22();
	InitMenus();

	MSG mMessage;

	TCHAR mainWndClassName[] = L"Chat.project";

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

	hInstCopy = hInst;
	nCmdShowCopy = nCmdShow;

	hMainWnd = CreateWindowEx(NULL, mainWndClassName, L"Chat.project", MY_LOG_WND_STYLE, CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480, NULL, NULL, hInst, NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, L"Window don't create", L"Error", MB_OK);
		return 1;
	}

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

	LPDRAWITEMSTRUCT lpdrawstLogon = NULL;

	LPMINMAXINFO pInfo = NULL;
	POINT StartWndSize;

	static Gdiplus::Graphics* gdiImg = NULL;

	static int iWindowType(LOGIN_WINDOW);

	switch (uMsg)
	{
	case WM_CREATE:
	{
		if (iWindowType == LOGIN_WINDOW)
		{
			InitHandles(hWnd);

			SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~(WS_MAXIMIZEBOX));

			SetMenu(hWnd, hLogMenu);

			hdcMain = GetDC(0);
			int x, y;
			x = GetDeviceCaps(hdcMain, HORZRES);
			y = GetDeviceCaps(hdcMain, VERTRES);

			SetWindowPos(hWnd, NULL, ((x - 640) / 2), ((y - 480) / 2), 0, 0, SWP_NOSIZE);

			ReleaseDC(0, hdcMain);

			InvalidateRect(hWnd, NULL, TRUE);
			SetWindowPos(hWnd, HWND_TOP, 0, 0, 640, 480, SWP_NOMOVE);
		}
		else if (iWindowType == CONNECTING_WINDOW)
		{
			SetMenu(hWnd, NULL);
			hdcMain = GetDC(0);
			int x, y;
			x = GetDeviceCaps(hdcMain, HORZRES);
			y = GetDeviceCaps(hdcMain, VERTRES);

			SetWindowPos(hWnd, NULL, ((x - 640) / 2), ((y - 480) / 2), 0, 0, SWP_NOSIZE);

			ReleaseDC(0, hdcMain);

			DestroyWindow(hLogin);
			DestroyWindow(hPass);
			DestroyWindow(hLogButton);

			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (iWindowType == CHAT_WINDOW)
		{
			SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | WS_MAXIMIZEBOX);

			SetMenu(hWnd, hChatMenu);

			hdcMain = GetDC(0);
			int x, y;
			x = GetDeviceCaps(hdcMain, HORZRES);
			y = GetDeviceCaps(hdcMain, VERTRES);

			SetWindowPos(hWnd, NULL, ((x - 900) / 2), ((y - 550) / 2), 0, 0, SWP_NOSIZE);

			ReleaseDC(0, hdcMain);

			SetWindowPos(hWnd, HWND_TOP, 0, 0, 900, 550, SWP_NOMOVE);

			RECT recTest;
			GetClientRect(hWnd, &recTest);
			//CloseWindow(hLogin); VERY FUNY RESULT! ^^
			HWND hTypeMessage = CreateWindow(L"RICHEDIT50W", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE , recTest.right - 560, recTest.bottom - 110, 550, 80, hWnd, (HMENU)12345, hInstCopy, NULL);
			HWND hContactsList = CreateWindow(L"RICHEDIT50W", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE, recTest.left + 10, 10, 270, recTest.bottom - 20, hWnd, (HMENU)141231, hInstCopy, NULL);
			
			recTest.top += 40;
			CHARRANGE ch;
			ch.cpMin = 0;
			ch.cpMax = -1;

			FORMATRANGE ft;
			ft.hdc = GetDC(hTypeMessage);
			ft.rc = recTest;
			ft.rcPage = recTest;
			ft.hdcTarget = NULL;
			ft.chrg = ch;
			SendMessage(hTypeMessage, EM_FORMATRANGE, 1, (LPARAM)&ft);
			//SetWindowPos(hWnd, HWND_TOP, 0, 0, 900, 550, SWP_NOMOVE);
		}
	}
	break;
	case WM_PAINT:
	{
		if (iWindowType == LOGIN_WINDOW)
		{
			hdcMain = BeginPaint(hWnd, &pstMain);

			SetTextColor(hdcMain, RGB(200, 200, 200));
			SetBkColor(hdcMain, RGB(4, 37, 65));

			SelectObject(hdcMain, hfSegoe_22);

			SetTextAlign(hdcMain, TA_RIGHT);
			TextOutW(hdcMain, 210, 270, L"Password", 8);
			TextOutW(hdcMain, 210, 190, L"Login", 5);
			SetTextAlign(hdcMain, TA_LEFT);

			gdiImg = new Gdiplus::Graphics(hdcMain);

			gdiImg->DrawImage(SimpleImgLoad.GetImg(ID_LOGO, hInstCopy), 256, 40, 128, 128);
			SimpleImgLoad.Release();

			delete gdiImg;

			EndPaint(hWnd, &pstMain);
		}
		else if (iWindowType == CHAT_WINDOW)
		{
			hdcMain = BeginPaint(hWnd, &pstMain);

			SetBkColor(hdcMain, RGB(4, 37, 65));
			//RoundRect(hdcMain, 20, 250, 400, 350, 50, 50);
			
			EndPaint(hWnd, &pstMain);
		}
		else if (iWindowType == CONNECTING_WINDOW)
		{
			hdcMain = BeginPaint(hWnd, &pstMain);

			SetBkColor(hdcMain, RGB(4, 37, 65));

			EndPaint(hWnd, &pstMain);
		}
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_LOGON && HIWORD(wParam) == BN_CLICKED)
		{
			iWindowType = CONNECTING_WINDOW;
			SetTimer(hWnd, ID_LOG_ANIM_TIMER, 50, NULL);
			SendMessage(hWnd, WM_CREATE, wParam, lParam);
		}
	}
	break;
	case WM_KEYUP: //FOR DEBUG
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			if (iWindowType == CHAT_WINDOW)
			{
				iWindowType = LOGIN_WINDOW;
				SendMessage(hWnd, WM_CREATE, wParam, lParam);
			}
		}
		break;
		}
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case ID_LOG_ANIM_TIMER:
		{
			static int iKillStep = 0;
			static int iImg = ID_LOGIN_ANIM_START;
			hdcMain = GetDC(hWnd);

			gdiImg = new Gdiplus::Graphics(hdcMain);
			gdiImg->DrawImage(SimpleImgLoad.GetImg(iImg, hInstCopy), 160, 150, 320, 180);
			SimpleImgLoad.Release();

			delete gdiImg;
			ReleaseDC(hWnd, hdcMain);

			iKillStep++;
			if (iKillStep == 8)
			{
				iWindowType = CHAT_WINDOW;
				iKillStep = 0;
				KillTimer(hWnd, ID_LOG_ANIM_TIMER);
				SendMessage(hWnd, WM_CREATE, wParam, lParam);
			}

			if (iImg < ID_LOGIN_ANIM_LAST)
			{
				iImg++;
			}
			else
			{
				iImg = ID_LOGIN_ANIM_START;
			}
		}
		break;
		}
	}
	break;
	case WM_DRAWITEM:
	{
		if (iWindowType == LOGIN_WINDOW)
		{
			lpdrawstLogon = (LPDRAWITEMSTRUCT)lParam;

			if (lpdrawstLogon->hwndItem == hLogButton)
			{
				FillRect(lpdrawstLogon->hDC, &lpdrawstLogon->rcItem, CreateSolidBrush(RGB(4, 37, 65)));

				gdiImg = new Gdiplus::Graphics(lpdrawstLogon->hDC);
				gdiImg->DrawImage(SimpleImgLoad.GetImg(ID_LOGON_DEF, hInstCopy), 0, 0, 48, 48);
				SimpleImgLoad.Release();

				switch (lpdrawstLogon->CtlID)
				{
				case ID_LOGON:
				{
					if (lpdrawstLogon->itemState & ODS_FOCUS)
					{
						FillRect(lpdrawstLogon->hDC, &lpdrawstLogon->rcItem, CreateSolidBrush(RGB(4, 37, 65)));

						gdiImg->DrawImage(SimpleImgLoad.GetImg(ID_LOGON_SET, hInstCopy), 0, 0, 48, 48);
						SimpleImgLoad.Release();
					}
				}

				delete gdiImg;

				break;
				}
			}
		}
	}
	break;
	case WM_SETCURSOR:
	{
		static HWND hFocused(NULL);
		if (hLogButton == (HWND)wParam)
		{
			if (GetFocus() != hLogButton)
			{
				hFocused = GetFocus();
				SetFocus(hLogButton);
			}
		}
		else
		{
			if (GetFocus() == hLogButton)
			{
				SetFocus(hFocused);
			}
		}
		DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	break;
	case WM_GETMINMAXINFO:
	{
		if (iWindowType == LOGIN_WINDOW || iWindowType == CONNECTING_WINDOW)
		{
			pInfo = (LPMINMAXINFO)lParam;
			StartWndSize = { 640, 480 };
			pInfo->ptMinTrackSize = StartWndSize;
			pInfo->ptMaxTrackSize = StartWndSize;
		}
		else if (iWindowType == CHAT_WINDOW)
		{
			pInfo = (LPMINMAXINFO)lParam;
			StartWndSize = { 900, 550 };
			pInfo->ptMinTrackSize = StartWndSize;
		}
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