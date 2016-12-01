#include "MyProcedures.h"

LRESULT CALLBACK LoginEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
	{
		if (wParam == VK_TAB)
		{
			SetFocus(hPass);
		}
		else if (search(wchAccesChar, wParam, sizeof(wchAccesChar)))
		{
			return CallWindowProc(wpLogin, hWnd, uMsg, wParam, lParam);
		}
	}
	break;
	default:
		return CallWindowProc(wpLogin, hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK LoginPassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
	{
		if (wParam == VK_TAB)
		{
			SetFocus(hLogButton);
			break;
		}
		else if (search(wchAccesChar, wParam, sizeof(wchAccesChar)))
		{
			return CallWindowProc(wpPass, hWnd, uMsg, wParam, lParam);
		}
	}
	break;
	default:
		return CallWindowProc(wpPass, hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK LogonProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
		{
			SetFocus(hLogin);
		}
		else if (wParam == VK_RETURN)
		{
			SendNotifyMessage(hMainWnd, WM_COMMAND, ID_LOGON | BN_CLICKED, NULL);
		}
		break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_LOGON)
		{
			MessageBox(NULL, L"YES\n!", L"OK", MB_OK);
		}
	}
	break;
	default:
		return CallWindowProc(wpLogon, hLogButton, uMsg, wParam, lParam);
	}
	return 0;
}