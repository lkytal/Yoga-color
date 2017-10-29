#include "stdafx.h"
#include "windows.h"
#include "Wingdi.h"
#include "iostream"
#include <string>

using namespace std;

#pragma comment(lib,"gdi32.lib")

int SetColorTemper(int r, int g, int b)
{
	WORD gammaArray[3][256];

	const HDC gammaDC = GetDC(NULL);

	if (gammaDC != NULL)
	{
		for (int i = 0; i < 256; i++)
		{
			gammaArray[0][i] = i * r;
			gammaArray[1][i] = i * g;
			gammaArray[2][i] = i * b;
		}

		SetDeviceGammaRamp(gammaDC, gammaArray);

		ReleaseDC(NULL, gammaDC);
	}

	return 0;
}

int GetBrightLever()
{
	WORD gammaArray[3][256];

	const HDC gammaDC = GetDC(NULL);

	if (gammaDC != NULL)
	{
		GetDeviceGammaRamp(gammaDC, static_cast<LPVOID>(gammaArray));

		for (int i = 1; i < 10; i++)
		{
			cout << "\nLevel %d    " << i;

			cout << "R: %d,  " << gammaArray[0][i] / i;
			cout << "G: %d,  " << gammaArray[1][i] / i;
			cout << "B: %d   " << gammaArray[2][i] / i;
		}

		ReleaseDC(NULL, gammaDC);
	}

	return 0;
}

#ifdef _WINDOWAPP

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	int R = 255, G = 250, B = 253;

	if (lpCmdLine[0] != NULL)
	{
		lpCmdLine[3] = lpCmdLine[7] = '\0';

		R = stoi(lpCmdLine);
		G = stoi(&lpCmdLine[4]);
		B = stoi(&lpCmdLine[8]);
	}

	SetColorTemper(R, G, B);

	return 0;
}

#else

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 4)
	{
		SetColorTemper(_ttoi(argv[1]), _ttoi(argv[2]), _ttoi(argv[3]));
	}

	GetBrightLever();

	return 0;
}

#endif
