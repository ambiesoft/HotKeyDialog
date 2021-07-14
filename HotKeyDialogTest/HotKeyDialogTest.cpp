// HotKeyDialogTest.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "HotKeyDialogTest.h"
#include "../HotKeyDialog/HotKeyDialog.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    WORD vk = 0;
    HWND h = nullptr;
    GetHotKeyFromUser(h,&vk);
    GetHotKeyFromUser(h,&vk);

}