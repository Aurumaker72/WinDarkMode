/*
 * Copyright (c) 2026, Aurumaker72.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma warning(push, 0)
#include "../WinDarkMode.h"
#pragma warning(pop)

#include <CommCtrl.h>
#include <string>
#include "resource.h"

static HWND m_hwnd_status = nullptr;

static void set_theme(WinDarkMode::Theme theme)
{
    WinDarkMode::set(theme);

    const wchar_t *label = L"Theme: System";
    if (theme == WinDarkMode::Theme::Light)
        label = L"Theme: Light";
    else if (theme == WinDarkMode::Theme::Dark)
        label = L"Theme: Dark";

    if (m_hwnd_status) SendMessage(m_hwnd_status, SB_SETTEXT, 0, reinterpret_cast<LPARAM>(label));
}

static INT_PTR CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG: {
        m_hwnd_status = CreateWindowEx(0, STATUSCLASSNAMEW, nullptr, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
                                       hwnd, nullptr, GetModuleHandle(nullptr), nullptr);
        SendMessage(m_hwnd_status, SB_SETTEXT, 0, reinterpret_cast<LPARAM>(L"Theme: System (follow OS)"));

        CheckRadioButton(hwnd, IDC_THEME_LIGHT, IDC_THEME_SYSTEM, IDC_THEME_SYSTEM);

        HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
        SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Option Alpha"));
        SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Option Beta"));
        SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Option Gamma"));
        SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Option Delta"));
        SendMessage(hCombo, CB_SETCURSEL, 0, 0);

        HWND hList = GetDlgItem(hwnd, IDC_LIST1);
        for (int i = 1; i <= 8; ++i)
        {
            std::wstring item = L"List item " + std::to_wstring(i);
            SendMessage(hList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(item.c_str()));
        }

        HWND hTab = GetDlgItem(hwnd, IDC_TAB1);
        TCITEMW tci = {};
        tci.mask = TCIF_TEXT;
        const wchar_t *tabs[] = {L"General", L"Advanced", L"About"};
        for (int i = 0; i < 3; ++i)
        {
            tci.pszText = const_cast<LPWSTR>(tabs[i]);
            TabCtrl_InsertItem(hTab, i, &tci);
        }

        SetDlgItemText(hwnd, IDC_EDIT1, L"Type something here...");

        WinDarkMode::attach(hwnd);

        return TRUE;
    }

    case WM_SIZE:
        if (m_hwnd_status) SendMessage(m_hwnd_status, WM_SIZE, wParam, lParam);
        return FALSE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_THEME_LIGHT:
            set_theme(WinDarkMode::Theme::Light);
            return TRUE;
        case IDC_THEME_DARK:
            set_theme(WinDarkMode::Theme::Dark);
            return TRUE;
        case IDC_THEME_SYSTEM:
            set_theme(WinDarkMode::Theme::System);
            return TRUE;
        case IDC_BUTTON1:
            MessageBox(hwnd, L"Hello from WinDarkMode!\n\nThis demo shows dark mode applied to a Win32 dialog.",
                       L"WinDarkMode Demo", MB_OK | MB_ICONINFORMATION);
            return TRUE;
        case IDCANCEL:
            DestroyWindow(hwnd);
            return TRUE;
        }
        return FALSE;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return TRUE;

    case WM_DESTROY:
        m_hwnd_status = nullptr;
        PostQuitMessage(0);
        return TRUE;
    }

    return FALSE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nShowCmd)
{
    INITCOMMONCONTROLSEX icc = {};
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_WIN95_CLASSES | ICC_TAB_CLASSES | ICC_BAR_CLASSES;
    InitCommonControlsEx(&icc);

    WinDarkMode::init();
    WinDarkMode::set(WinDarkMode::Theme::System);

    HWND hwnd = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), nullptr, DlgProc, 0);

    if (!hwnd) return 1;

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!IsDialogMessage(hwnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}
