#include <iostream>
#include <string>
#include <Windows.h>

#include "MainWindow.h"

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pCmdLine,
	_In_ int nCmdShow
)
{
	MainWindow window{};
	window.Show();

    return 0;
}