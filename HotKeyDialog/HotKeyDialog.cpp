// HotKeyDialog.cpp : Defines the exported functions for the DLL.
//


#include "resource.h"
#include "framework.h"
#include <string>
#include <cassert>
#include "../../lsMisc/CenterWindow.h"

#include "HotKeyDialog.h"

using namespace Ambiesoft;

extern HMODULE ghInstance;
struct DialogData {
	WORD* key_;
	HWND h_;
	LPCWSTR pTitle_;
	DialogData(WORD* key, HWND h, LPCWSTR pTitle):
		key_(key),
		h_(h),
		pTitle_(pTitle){}
};

WNDPROC oldproc;
LRESULT CALLBACK hotkeyProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	if (uMsg == WM_COMMAND && LOWORD(wParam) == EN_CHANGE)
	{
		HWND hEdit = (HWND)lParam;
	}
	return oldproc(hwnd, uMsg, wParam, lParam);
}
INT_PTR CALLBACK dialogProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	static HWND hHot;
	static DialogData* pDD;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		hHot = GetDlgItem(hDlg, IDC_HOTKEY_KEY);
		assert(::IsWindow(hHot));
		// oldproc = (WNDPROC)SetWindowLong(hHot, GWL_WNDPROC, (LPARAM)hotkeyProc);
		
		pDD = (DialogData*)lParam;
		assert(pDD);
		SendMessage(hHot, HKM_SETHOTKEY, *pDD->key_, 0);
		SetWindowText(hDlg, pDD->pTitle_);
		CenterWindow(hDlg, pDD->h_);
		return TRUE;
	}
	break;
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case EN_CHANGE:
		{
			WORD idEditHotKey = LOWORD(wParam);
			HWND hEditHotKey = (HWND)lParam;
			wchar_t szT[200];
			GetWindowText(hEditHotKey, szT, 125);
			SendMessage(hEditHotKey, WM_GETTEXT, 125, (LPARAM)szT);
		}
			break;
		case IDOK:
			*pDD->key_ = LOWORD(SendMessage(hHot, HKM_GETHOTKEY, 0, 0));
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	break;


	}

	return FALSE;
}

// This is an example of an exported function.
HOTKEYDIALOG_API bool GetHotKeyFromUser(HWND hParent, const wchar_t* title, WORD* key)
{
	DialogData data(key, hParent, title);
	INT_PTR ret = DialogBoxParam(ghInstance,
		MAKEINTRESOURCE(IDD_DIALOG_HOTKEY),
		hParent,
		dialogProc,
		(LPARAM)&data);
	
	return ret==IDOK;
}

