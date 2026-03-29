# Contributing

## Prerequisites

- Windows 10 or later
- [CMake](https://cmake.org/) 3.20 or later
- A C++23-capable compiler with Windows SDK support (e.g. MSVC via [Visual Studio 2022](https://visualstudio.microsoft.com/) or the Build Tools)

## Running the test project

The `test/` directory contains a minimal Win32 dialog application that exercises `WinDarkMode`.

### 1. Configure

From the repository root, run:

```sh
cmake -S test -B test/build
```

### 2. Build

```sh
cmake --build test/build
```

### 3. Run

```sh
test\build\Debug\WinDarkModeTest.exe
```

The app opens a small dialog with dark mode applied via `WinDarkMode::attach()` in `WM_INITDIALOG`. Close it with the **OK** button or the title-bar close button.
