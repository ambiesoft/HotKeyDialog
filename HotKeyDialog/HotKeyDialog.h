// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the HOTKEYDIALOG_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// HOTKEYDIALOG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once
#ifdef HOTKEYDIALOG_EXPORTS
#define HOTKEYDIALOG_API __declspec(dllexport)
#else
#define HOTKEYDIALOG_API __declspec(dllimport)
#endif

// key: inout
// return: true if user choose OK, otherwise false
HOTKEYDIALOG_API bool GetHotKeyFromUser(HWND hParent, const wchar_t* title, WORD* key);
