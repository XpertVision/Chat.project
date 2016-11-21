#ifndef _HEADER_H_
#define _HEADER_H_

#include <Windows.h>
#include <gdiplus.h>
#include <Richedit.h>

#pragma comment (lib,"Gdiplus.lib")

#include "resource.h"
#include "LogPassChar.h"
#include "LoadImgRes.h"
#include "InitHandles.h"

#define LOGIN_WINDOW      0
#define CHAT_WINDOW       1
#define CONNECTING_WINDOW 2

#define ID_LOGON 777

#define ID_LOG_ANIM_TIMER 3000

#endif // !_HEADER_H_