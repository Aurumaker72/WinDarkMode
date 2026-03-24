> [!WARNING]
> This library is not production-ready.
> It's lacking essential functionality, but it's also being worked on actively.
> 
> Check back later! 

# WinDarkMode

Single-header Win32 dark mode library with a sane and modern API surface based on [win32-darkmode](https://github.com/ysc3839/win32-darkmode).

## Why?

The original win32-darkmode isn't easily embeddable and therefore a nightmare to work with.

This version aims to fix that, while also providing convenience features, bugfixes, and Windows 11 support.

## Quickstart

1. Download `WinDarkMode.h` and drop into your project
2. Include it via `#include "WinDarkMode.h"`
3. Initialize it in WinMain `WinDarkMode::init()`
4. Attach it to a window `WinDarkMode::attach(hwnd)`

```cpp
#include "WinDarkMode.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_CREATE:
            WinDarkMode::attach(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return TRUE;
}

int CALLBACK WinMain(const HINSTANCE hInstance, HINSTANCE, LPSTR, const int nShowCmd)
{
    WinDarkMode::init();
    RegisterClassEx...
    CreateWindow...
}
```

## Attaching to dialogs

WinDarkMode supports attaching to both top-level windows and dialogs.

To attach to a dialog, you still call `WinDarkMode::attach(hwnd);`, but preferrably on `WM_INITDIALOG`. 

`WM_CREATE` should work too, but is less common.
