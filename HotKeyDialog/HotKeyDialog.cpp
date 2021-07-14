// HotKeyDialog.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "resource.h"
#include "framework.h"
#include <string>
#include <cassert>
#include "../../lsMisc/CenterWindow.h"

#include "HotKeyDialog.h"

using namespace Ambiesoft;

HWND ghParent;

INT_PTR CALLBACK dialogProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	static HWND hHot;
	static WORD* pRetKey;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		hHot = GetDlgItem(hDlg, IDC_HOTKEY_KEY);
		assert(::IsWindow(hHot));
		pRetKey = (WORD*)lParam;
		assert(pRetKey);
		SendMessage(hHot, HKM_SETHOTKEY, *pRetKey, 0);

		CenterWindow(hDlg, ghParent);
		return TRUE;
	}
	break;
	
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDOK:
			*pRetKey = LOWORD(SendMessage(hHot, HKM_GETHOTKEY, 0, 0));
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
HOTKEYDIALOG_API bool GetHotKeyFromUser(HWND hParent, WORD* key)
{
	ghParent = hParent;
	INT_PTR ret = DialogBoxParam(ghInstance,
		MAKEINTRESOURCE(IDD_DIALOG_HOTKEY),
		hParent,
		dialogProc,
		(LPARAM)key);
	
	return ret==IDOK;
}

