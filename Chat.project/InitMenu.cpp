#include "InitMenu.h"

void InitMenus()
{
	hChatMenu = LoadMenu(hInstCopy, MAKEINTRESOURCE(IDR_MENU_CHAT));
	hLogMenu = LoadMenu(hInstCopy, MAKEINTRESOURCE(IDR_MENU_LOGIN));
}